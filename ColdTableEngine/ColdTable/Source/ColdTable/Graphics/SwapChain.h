#pragma once

#include <ColdTable/Graphics/GraphicsResource.h>
#include <ColdTable/Graphics/DeviceContext.h>

namespace ColdTable {
	class SwapChain final: public GraphicsResource
	{
	public:
		SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& graphicsDesc);

	public: 
		void Present(bool vsync = false);

	private:
		void reloadBuffer();

	private:
		Microsoft::WRL::ComPtr<IDXGISwapChain> _swapChain;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> _renderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> _frameBuffer;
		Microsoft::WRL::ComPtr <ID3D11DepthStencilView> _depthStencilView;

	private:
		friend class DeviceContext;
	};
}

