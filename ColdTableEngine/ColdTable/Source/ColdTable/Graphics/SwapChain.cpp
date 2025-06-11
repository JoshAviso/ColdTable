#include <ColdTable/Graphics/SwapChain.h>

ColdTable::SwapChain::SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& graphicsDesc): GraphicsResource(graphicsDesc)
{
	DXGI_SWAP_CHAIN_DESC dxgiDesc{};

	dxgiDesc.BufferDesc.Width = std::max(1, desc.windowSize.width);
	dxgiDesc.BufferDesc.Height = std::max(1, desc.windowSize.height);
	dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	dxgiDesc.BufferCount = 2;
	dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

	dxgiDesc.OutputWindow = static_cast<HWND>(desc.windowHandle);
	dxgiDesc.SampleDesc.Count = 1;
	dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	dxgiDesc.Windowed = true;

	ColdTableGraphicsLogThrowOnFail(_factory.CreateSwapChain(&_device, &dxgiDesc,&_swapChain),
		"CreateSwapChain failed.");

	reloadBuffer();

	D3D11_TEXTURE2D_DESC depthDesc{};
	depthDesc.Width = desc.windowSize.width;
	depthDesc.Height = desc.windowSize.height;
	depthDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthDesc.Usage = D3D11_USAGE_DEFAULT;
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthDesc.MipLevels = 1;
	depthDesc.SampleDesc.Count = 1;
	depthDesc.SampleDesc.Quality = 0;
	depthDesc.MiscFlags = 0;
	depthDesc.ArraySize = 1;
	depthDesc.CPUAccessFlags = 0;

	ColdTableGraphicsLogThrowOnFail(
	    _device.CreateTexture2D(&depthDesc, nullptr, &_frameBuffer),
		"Create SwapChain failed."
	)

	ColdTableGraphicsLogThrowOnFail(
	    _device.CreateDepthStencilView(_frameBuffer.Get(), NULL, &_depthStencilView),
		"Create SwapChain failed."
	)
}

void ColdTable::SwapChain::Present(bool vsync)
{
	ColdTableGraphicsLogThrowOnFail(
		_swapChain->Present(vsync, 0),
		"Present failed."
	)
}

void ColdTable::SwapChain::reloadBuffer()
{
	ColdTableGraphicsLogThrowOnFail(
		_swapChain->GetBuffer(0, IID_PPV_ARGS(&_frameBuffer)),
		"GetBuffer failed."
	)
	ColdTableGraphicsLogThrowOnFail(
		_device.CreateRenderTargetView(_frameBuffer.Get(), nullptr, &_renderTargetView),
		"CreateRenderTargetView failed."
	)

}
