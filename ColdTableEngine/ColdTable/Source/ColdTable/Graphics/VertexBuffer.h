#pragma once
#include <d3d11.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>

namespace ColdTable
{

	class VertexBuffer : public Base
	{
	public:
		explicit VertexBuffer(VertexBufferDesc desc);
		virtual ~VertexBuffer() override;
		void LoadVertices(void* list, UINT vertexSize, UINT listSize, void* shaderByteCode, UINT shaderByteSize);

		UINT GetVertexCount();

	private:
		UINT _vertexSize;
		UINT _listSize;

	private:
		GraphicsDevicePtr _graphicsDevice{};

		ID3D11Buffer* _buffer;
		ID3D11InputLayout* _layout;

	private:
		friend class DeviceContext;
	};
}
 