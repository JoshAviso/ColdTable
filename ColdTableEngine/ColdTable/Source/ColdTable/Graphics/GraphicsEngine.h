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

		void Render(SwapChain& swapChain, VertexBufferPtr vertexBuffer, Rect viewportSize, ShaderPtr shader);
		void SetViewportSize(Rect size);

		VertexBufferPtr CreateVertexBuffer();

		ShaderPtr CreateShader(wchar_t* vertexShaderSrc, wchar_t* pixelShaderSrc);
		void UseShader(const ShaderPtr& shader);

	private:
		std::shared_ptr<GraphicsDevice> _graphicsDevice{};
		DeviceContextPtr _deviceContext{};
	};
}

