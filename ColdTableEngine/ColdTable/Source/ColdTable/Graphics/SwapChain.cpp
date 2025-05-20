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
;}

void ColdTable::SwapChain::Present(bool vsync)
{
	ColdTableGraphicsLogThrowOnFail(_swapChain->Present(vsync, 0),
		"Present failed.");
}

void ColdTable::SwapChain::reloadBuffer()
{
	Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer{};
	ColdTableGraphicsLogThrowOnFail(_swapChain->GetBuffer(0, IID_PPV_ARGS(&buffer)),
		"GetBuffer failed.");
	ColdTableGraphicsLogThrowOnFail(_device.CreateRenderTargetView(buffer.Get(), nullptr, &_renderTargetView),
		"CreateRenderTargetView failed.");

}
