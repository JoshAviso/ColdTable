#include "VertexObject.h"

#include "ColdTable/Graphics/VertexBuffer.h"
#include "ColdTable/Graphics/Renderables/Renderable.h"

ColdTable::VertexObject::VertexObject(VertexBufferPtr owner): _owner(owner)
{
}

ColdTable::VertexObject::VertexObject(VertexBufferPtr owner, unsigned int vertexIndex): _owner(owner)
{
	transform.position = owner->_vertices[vertexIndex]->position;
	Vec3 position = owner->_vertices[vertexIndex]->position;
	for (int i = 0; i < _owner->_vertices.size(); i++)
	{
		VertexPtr vertex = _owner->_vertices[i];
		if ((position - vertex->position).magnitudeSqrd() <= 0.00001f)
		{
			_vertexIndices.push_back(i);
			tempPos = vertex->position;
			transform.position = vertex->position;
		}
	}
}

ColdTable::VertexObject::VertexObject(VertexBufferPtr owner, unsigned int vertexIndex, Vec3 pos) : _owner(owner), tempPos(pos)
{
	transform.position = pos;
	_vertexIndices.push_back(vertexIndex);
}

void ColdTable::VertexObject::AddVertex(unsigned int vertexIndex)
{
	if (std::find(_vertexIndices.begin(), _vertexIndices.end(), vertexIndex) != _vertexIndices.end())
		return;
	_vertexIndices.push_back(vertexIndex);
}

void ColdTable::VertexObject::Translate(Vec3 translation)
{
	transform.position += translation;

    _owner->_canUpdateVertex = true;
	_owner->_isDirty = true;
    _owner->UpdateVertexData();
}

void ColdTable::VertexObject::Rotate(Vec3 axis, float degree)
{
	Quaternion rotation(axis, degree);
	transform.rotation.rotate(rotation);
	_owner->_canUpdateVertex = true;
	_owner->_isDirty = true;
	_owner->UpdateVertexData();
}

void ColdTable::VertexObject::Scale(Vec3 scale)
{
}

ColdTable::Vec3 ColdTable::VertexObject::getActualPos()
{
	Vec3 transformedVec = (Vec3)(	transform.transformMat() * vert()->position.asTranslationMatrix().inverse() * vert()->position);

	std::vector<FaceObject*> intersectingFaces;
	Vec3 blendedVecToEdges = Vec3::Zero;
	for (auto edge : _owningEdges)
	{
		for (auto face : edge->_owningFaces)
		{
			if (std::find(intersectingFaces.begin(), intersectingFaces.end(), face) == intersectingFaces.end())
				intersectingFaces.push_back(face);
		}

		blendedVecToEdges += (Vec3)(edge->transform.transformMat() * edge->originalTransform.transformMat().inverse() * transformedVec);
	}
	blendedVecToEdges *= 1.0f / (float)_owningEdges.size();
	Vec3 blendedVecToFaces = Vec3::Zero;
	for (auto face : intersectingFaces)
	{
		blendedVecToFaces += (Vec3)(face->transform.transformMat() * face->originalTransform.transformMat().inverse() * transformedVec);
	}
	blendedVecToFaces *= 1.0f / (float)intersectingFaces.size();

	Vec3 blendedVec = (blendedVecToEdges + blendedVecToFaces) * 0.5f;

	return blendedVec;

}

ColdTable::VertexPtr ColdTable::VertexObject::vert()
{
	return _owner->_vertices[_vertexIndices[0]];
}

void ColdTable::VertexObject::AddEdge(EdgeObject* edge)
{
	if (std::find(_owningEdges.begin(), _owningEdges.end(), edge) == _owningEdges.end())
		_owningEdges.push_back(edge);
}
