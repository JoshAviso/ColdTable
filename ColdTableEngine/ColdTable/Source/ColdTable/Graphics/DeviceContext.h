#pragma once
#include <d3d11.h>
#include <wrl.h>

#include <ColdTable/Graphics/GraphicsResource.h>
#include <ColdTable/Graphics/SwapChain.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Math/Vec4.h>
#include <ColdTable/Graphics/VertexBuffer.h>
#include <ColdTable/Graphics/ConstantBuffer.h>
#include <ColdTable/Graphics/Renderables/Renderable.h>


namespace ColdTable {

	class DeviceContext: public GraphicsResource
	{
	public:
		explicit DeviceContext(const GraphicsResourceDesc& desc);
		virtual ~DeviceContext() override;

		void ClearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color);
		void SetViewportSize(Rect size);
		void BindConstantBuffer(ConstantBufferPtr constantBuffer);
		void BindComputeShader(ComputeShaderPtr computeShader);
		void DispatchComputeShader(UINT xThreadGroups, UINT yThreadGroups, UINT zThreadGroups);

	public:
		void Draw(RenderablePtr renderable);

	private:
		void BindVertexBuffer(VertexBufferPtr vertexBuffer);
		void UseShader(ShaderPtr shader);
		void DrawTriangleList(UINT vertexCount, UINT startVertexIndex);
		void DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex);

	private:
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;

	private:
		friend class GraphicsDevice;
		friend class ConstantBuffer;
		friend class GraphicsEngine;
		friend class ComputeShader;
	};
}

