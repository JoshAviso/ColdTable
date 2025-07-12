#include "EdgeObject.h"

#include "ColdTable/Graphics/VertexBuffer.h"

ColdTable::EdgeObject::EdgeObject(VertexObjectPtr vert1, VertexObjectPtr vert2) : _vert1(vert1), _vert2(vert2)
{
	Vec3 originalCenter = (vert1->transform.position + vert2->transform.position) * 0.5f;
	Quaternion origRot = Quaternion::Identity;
	originalTransform.position = originalCenter;
	originalTransform.rotation = origRot;
	transform = originalTransform;

	vert1->AddEdge(this);
	vert2->AddEdge(this);
}

void ColdTable::EdgeObject::RecalcAabb()
{
	Vec3 vert1 = (Vec3)(_vert1->getActualPos());
	Vec3 vert2 = (Vec3)(_vert2->getActualPos());
	aabb_min = Vec3::min(vert1, vert2);
	aabb_max = Vec3::max(vert1, vert2);
}

void ColdTable::EdgeObject::Translate(Vec3 translation)
{
	transform.position += translation;
	_vert1->_owner->_canUpdateVertex = true;
	_vert1->_owner->_isDirty = true;
	_vert1->_owner->UpdateVertexData();
	_vert2->_owner->_canUpdateVertex = true;
	_vert2->_owner->_isDirty = true;
	_vert2->_owner->UpdateVertexData();
}

void ColdTable::EdgeObject::Rotate(Vec3 axis, float degree)
{
}

void ColdTable::EdgeObject::AddFace(FaceObject* face)
{
	if (std::find(_owningFaces.begin(), _owningFaces.end(), face) == _owningFaces.end())
		_owningFaces.push_back(face);
}
