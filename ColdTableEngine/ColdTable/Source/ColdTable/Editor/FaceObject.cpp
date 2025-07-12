#include "FaceObject.h"

#include "ColdTable/Core/Logger.h"
#include "ColdTable/Graphics/VertexBuffer.h"


ColdTable::FaceObject::FaceObject(Vec3 normal)
{
}

ColdTable::FaceObject::FaceObject(EdgeObjectPtr edge1, EdgeObjectPtr edge2, EdgeObjectPtr edge3, Vec3 normal) 
{
	_edges.push_back(edge1);
	_edges.push_back(edge2);
	_edges.push_back(edge3);

	Vec3 originalCenter = (edge1->originalTransform.position + edge2->originalTransform.position + edge3->originalTransform.position) * 1.0f / 3.0f;
	Quaternion origRot = Quaternion::Identity;
	originalTransform.position = originalCenter;
	originalTransform.rotation = origRot;
	transform = originalTransform;

	edge1->AddFace(this);
	edge2->AddFace(this);
	edge3->AddFace(this);
}

ColdTable::FaceObject::FaceObject(EdgeObjectPtr edge1, EdgeObjectPtr edge2, EdgeObjectPtr edge3, EdgeObjectPtr edge4, Vec3 normal)
{
	_edges.push_back(edge1);
	_edges.push_back(edge2);
	_edges.push_back(edge3);
	_edges.push_back(edge4);

	Vec3 originalCenter = (edge1->originalTransform.position + edge2->originalTransform.position + edge3->originalTransform.position + edge4->originalTransform.position) * 0.25f;
	Quaternion origRot = Quaternion::Identity;
	originalTransform.position = originalCenter;
	originalTransform.rotation = origRot;
	transform = originalTransform;

	edge1->AddFace(this);
	edge2->AddFace(this);
	edge3->AddFace(this);
	edge4->AddFace(this);
}

void ColdTable::FaceObject::AddEdge(EdgeObjectPtr edge)
{
	_edges.push_back(edge);
	edge->AddFace(this);

	Vec3 originalCenter = Vec3::Zero;
	for (auto edge : _edges)
	{
		originalCenter += edge->originalTransform.position;
	}
	originalCenter *= 1.0f / (float)_edges.size();

	Quaternion origRot = Quaternion::Identity;
	originalTransform.position = originalCenter;
	originalTransform.rotation = origRot;
	transform = originalTransform;
}

void ColdTable::FaceObject::RecalcAABB()
{
	float minX = 999999, minY = 999999, minZ = 999999;
	float maxX = -999999, maxY = -999999, maxZ = -999999;
	for (auto edge : _edges)
	{
		VertexObjectPtr v1 = edge->_vert1;
		VertexObjectPtr v2 = edge->_vert2;
		Vec3 vert1 = (Vec3)(v1->getActualPos());
		Vec3 vert2 = (Vec3)(v2->getActualPos());

		minX = std::min(minX, std::min(vert1.x, vert2.x));
		minY = std::min(minY, std::min(vert1.y, vert2.y));
		minZ = std::min(minZ, std::min(vert1.z, vert2.z));

		maxX = std::max(maxX, std::max(vert1.x, vert2.x));
		maxY = std::max(maxY, std::max(vert1.y, vert2.y));
		maxZ = std::max(maxZ, std::max(vert1.z, vert2.z));
	}
	aabb_min = Vec3(minX, minY, minZ);
	aabb_max = Vec3(maxX, maxY, maxZ);
	Logger::Log(Logger::LogLevel::Info, aabb_max.toString().c_str());
	Logger::Log(Logger::LogLevel::Info, aabb_min.toString().c_str());
}

void ColdTable::FaceObject::Translate(Vec3 translation)
{
	transform.position += translation;
	std::vector<VertexObjectPtr> vertlist;
	for (auto& edge : _edges)
	{
		VertexObjectPtr v1 = edge->_vert1;
		VertexObjectPtr v2 = edge->_vert2;
		if (std::find(vertlist.begin(), vertlist.end(), v1) == vertlist.end())
			vertlist.push_back(v1);
		if (std::find(vertlist.begin(), vertlist.end(), v2) == vertlist.end())
			vertlist.push_back(v2);
	}

	for (auto vertexObject : vertlist)
	{
		vertexObject->_owner->_canUpdateVertex = true;
		vertexObject->_owner->_isDirty = true;
		vertexObject->_owner->UpdateVertexData();
	}
}

void ColdTable::FaceObject::Rotate(Vec3 axis, float degree)
{
	transform.rotation.rotateWorld(axis, degree);
}

void ColdTable::FaceObject::Scale(Vec3 scale)
{
	transform.scale += scale;

	std::vector<VertexObjectPtr> vertlist;
	for (auto& edge : _edges)
	{
		VertexObjectPtr v1 = edge->_vert1;
		VertexObjectPtr v2 = edge->_vert2;
		if (std::find(vertlist.begin(), vertlist.end(), v1) == vertlist.end())
			vertlist.push_back(v1);
		if (std::find(vertlist.begin(), vertlist.end(), v2) == vertlist.end())
			vertlist.push_back(v2);
	}

	for (auto vertexObject : vertlist)
	{
		vertexObject->_owner->_canUpdateVertex = true;
		vertexObject->_owner->_isDirty = true;
		vertexObject->_owner->UpdateVertexData();
	}
}

ColdTable::Mat4 ColdTable::FaceObject::currentTransform()
{
	Vec3 runningTotal = Vec3::Zero;
	for (auto& edge : _edges)
	{
		VertexObjectPtr v1 = edge->_vert1;
		VertexObjectPtr v2 = edge->_vert2;
		Vec3 vert1 = (Vec3)(v1->transform.transformMat() * v1->vert()->position.asTranslationMatrix().inverse() * v1->vert()->position);
		Vec3 vert2 = (Vec3)(v2->transform.transformMat() * v2->vert()->position.asTranslationMatrix().inverse() * v2->vert()->position);
		runningTotal += (vert1 + vert2) * 0.5f;
	}
	Vec3 center = runningTotal / (float)_edges.size();
	return transform.rotation.asMat() * center.asTranslationMatrix();
}
