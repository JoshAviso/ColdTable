#pragma once

#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <vector>

namespace ColdTable
{
	class GraphicsEngine final: public Base 
	{
	public:
		explicit GraphicsEngine(const GraphicsEngineDesc& desc);
		virtual ~GraphicsEngine() override;

		void RegisterRenderable(RenderablePtr renderable);
		void UnregisterRenderable(RenderablePtr renderable);

		void RegisterComputeShader(ComputeShaderPtr computeShader);

		GraphicsDevicePtr GetGraphicsDevice() noexcept;
		void TickConstantBuffer(ColdTable::ConstantBufferPtr constantBuffer, bool isDeferred);

		void SetViewportSize(Rect size);
		ShaderPtr CreateShader(const wchar_t* vertexShaderSrc, const wchar_t* pixelShaderSrc);
		ComputeShaderPtr CreateComputeShader(const wchar_t* sourceFile, const float* inputArray);
		void BindComputeShader(ComputeShaderPtr computeShader);

		VertexBufferPtr CreateVertexBuffer();
		ConstantBufferPtr CreateConstantBuffer();

	private:
		void UseShader(const ShaderPtr& shader);
		void Render(SwapChain& swapChain, ConstantBufferPtr constantBuffer, Rect viewportSize);

		void DispatchComputeShader(ComputeShaderPtr computeShader, UINT xThreads, UINT yThreads, UINT zThreads);
		void AwaitComputeShaderFinish();

		std::shared_ptr<GraphicsDevice> _graphicsDevice{};
		DeviceContextPtr _deviceContext{};

		std::vector<RenderablePtr> _renderables{};

		ID3D11Query* _computeShaderQuery;

		friend class GameLoop;
	};
}

