#pragma once
#include <ColdTable/Resource/Resource.h>
#include <ColdTable/Graphics/GraphicsDevice.h>

namespace ColdTable
{
	
class Mesh: public Resource
{
public:
	Mesh(GraphicsDevicePtr sourceDevice, const wchar_t* fullpath, MaterialPtr material);
	virtual ~Mesh() override;

private:
	VertexBufferPtr _vertexBuffer;
	IndexBufferPtr _indexBuffer;

	MaterialPtr _material;

	friend GraphicsEngine;
	friend DeviceContext;
};
}

