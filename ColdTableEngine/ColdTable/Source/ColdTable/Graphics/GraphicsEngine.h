#pragma once

#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/DeviceContext.h>

namespace ColdTable
{
	class GraphicsEngine final: public Base 
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		GraphicsDevicePtr GetGraphicsDevice() noexcept;

		void SetViewportSize(Rect size);
		ShaderPtr CreateShader(wchar_t* vertexShaderSrc, wchar_t* pixelShaderSrc);

		VertexBufferPtr CreateVertexBuffer();
		ConstantBufferPtr CreateConstantBuffer();

	private:
		void UseShader(const ShaderPtr& shader);
		void Render(SwapChain& swapChain, RenderablePtr renderable, ConstantBufferPtr constantBuffer, Rect viewportSize);

		std::shared_ptr<GraphicsDevice> _graphicsDevice{};
		DeviceContextPtr _deviceContext{};


		friend class GameLoop;
	};
}

