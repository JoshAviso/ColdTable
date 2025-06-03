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

	private:
		UINT GetVertexCount();
		void LoadVertices(const void* list, UINT vertexSize, UINT listSize, ShaderPtr shader);
		UINT _vertexSize;
		UINT _listSize;
		
	private:

		ID3D11Buffer* _buffer;
		ID3D11InputLayout* _layout;

	private:
		friend class DeviceContext;
		friend class Renderable;
	};
}
 