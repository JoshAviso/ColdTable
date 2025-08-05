#include <algorithm>
#include <string>
#include <ColdTable/Graphics/Renderables/Renderable.h>

#include <ColdTable/Graphics/EngineShader.h>
#include <ColdTable/Graphics/VertexBuffer.h>

#include "ColdTable/Resource/Material/Material.h"

ColdTable::Renderable::Renderable(const Renderable& other) :
	Renderable(
		{nullptr, 0, other._drawMode, other._material },
		other._shader
	)
{

	if (other._indexBuffer != nullptr)
	{
		//LoadVerticesInIndex();
	} else
	{
		LoadVertices(other.vertexListRef, other._vertexBuffer->_vertexObjects.size());
	}


	_vertexBuffer = other._vertexBuffer;
	_indexBuffer = other._indexBuffer;
	aabb_max = other.aabb_max;
	aabb_min = other.aabb_min;
}

ColdTable::Renderable::Renderable(const RenderableDesc& desc) : _shader(0), _drawMode(desc.drawMode), _material(desc.material)
{
	VertexBufferDesc bufferDesc{ {} };
	_vertexBuffer = std::make_shared<VertexBuffer>(bufferDesc);
	if (desc.vertexCount > 0)
		LoadVertices(desc.vertexList, desc.vertexCount);
}

ColdTable::Renderable::Renderable(const RenderableDesc& desc, const ShaderPtr& shader) : _shader(shader), _drawMode(desc.drawMode), _material(desc.material)
{
	VertexBufferDesc bufferDesc{ {} };
	_vertexBuffer = std::make_shared<VertexBuffer>(bufferDesc);
	if (desc.vertexCount > 0)
		LoadVertices(desc.vertexList, desc.vertexCount);
}

ColdTable::Renderable::~Renderable()
{

}

void ColdTable::Renderable::LoadVertices(const Vertex* vertexList, UINT listSize)
{
	if (_indexBuffer) _indexBuffer = nullptr;

	vertexListRef = vertexList;

	if (_material == nullptr)
	{
		_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _shader);

	} else
	{
		_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _material->_shader);
		
	}
}

void ColdTable::Renderable::LoadVerticesInIndex(const Vertex* vertexList, UINT listSize, const IndexBufferPtr& indexBuffer)
{
	_indexBuffer = indexBuffer;

	vertexListRef = vertexList;

	if (_material == nullptr)
	{
		_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _shader);

	}
	else
	{
		_vertexBuffer->LoadVertices(vertexList, sizeof(Vertex), listSize, _material->_shader);

	}
}

void ColdTable::Renderable::ReloadVertices()
{
	_vertexBuffer->UpdateVertexData();
}

ColdTable::Mat4 ColdTable::Renderable::transformMat() const
{
	Mat4 scaleMat = localScale.asScaleMatrix();
	Mat4 translateMat = localPosition.asTranslationMatrix();

	return translateMat * static_cast<Mat4>(localRotation) * scaleMat;
}

void ColdTable::Renderable::recalcAABB()
{
	Mat4 modelMat = localScale.asScaleMatrix();

	float minX = 1000000.0f, minY = 1000000.0f, minZ = 1000000.0f;
	float maxX = -1000000.0f, maxY = -1000000.0f, maxZ = -1000000.0f;
	if (_vertexBuffer->_vertexObjects.size() <= 0)
	{
		aabb_max = Vec3(0.0f, 0.0f, 0.0f);
		aabb_min = Vec3(0.0f, 0.0f, 0.0f);
		return;
	}
	for (auto vert : _vertexBuffer->_vertexObjects)
	{
		Vec3 transformedVert = Vec3(modelMat * vert->getActualPos());
		minX = std::min(transformedVert.x, minX);
		minY = std::min(transformedVert.y, minY);
		minZ = std::min(transformedVert.z, minZ);
		maxX = std::max(transformedVert.x, maxX);
		maxY = std::max(transformedVert.y, maxY);
		maxZ = std::max(transformedVert.z, maxZ);
	}
	aabb_max = Vec3(maxX, maxY, maxZ);
	aabb_min = Vec3(minX, minY, minZ);
}
