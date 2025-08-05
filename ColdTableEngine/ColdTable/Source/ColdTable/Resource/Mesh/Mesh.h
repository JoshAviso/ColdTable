#pragma once
#include <ColdTable/Resource/Resource.h>
#include <ColdTable/Graphics/GraphicsDevice.h>

namespace ColdTable
{
	
class Mesh: public Resource
{
public:
	Mesh(RenderablePtr renderable);
	Mesh(GraphicsDevicePtr sourceDevice, const Vertex* vertexList, UINT vertexCount);
	Mesh(GraphicsDevicePtr sourceDevice, const Vertex* vertexList, UINT vertexCount, const void* indexList, UINT indexCount);
	Mesh(GraphicsDevicePtr sourceDevice, const wchar_t* full_path);
	Mesh(GraphicsDevicePtr sourceDevice, const wchar_t* full_path, MaterialPtr material);
	virtual ~Mesh() override;

	Transform transform{};

	bool GetAABB(Vec3& aabb_min, Vec3& aabb_max);
private:

	VertexBufferPtr _vertexBuffer;
	IndexBufferPtr _indexBuffer;

	MaterialPtr _material;

	friend GraphicsEngine;
	friend DeviceContext;
};
}

