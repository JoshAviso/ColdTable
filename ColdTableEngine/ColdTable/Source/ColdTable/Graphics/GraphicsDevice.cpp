
#include <ColdTable/Graphics/GraphicsDevice.h>

using namespace ColdTable;

GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc):
	Base(desc.base)
{
	D3D_FEATURE_LEVEL featureLevel{};
	UINT createDeviceFlags{};

#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	ColdTableGraphicsLogThrowOnFail(
		D3D11CreateDevice(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			createDeviceFlags,
			NULL, 0,
			D3D11_SDK_VERSION,
			&_d3dDevice,
			&featureLevel,
			&_d3dContext
		),
		"Direct3D11 initialization failed."
	);

	ColdTableGraphicsLogThrowOnFail(_d3dDevice->QueryInterface(IID_PPV_ARGS(&_dxgiDevice)),
		"QueryInterface failed to retrieve IDXGIDevice.");

	ColdTableGraphicsLogThrowOnFail(_dxgiDevice->GetParent(IID_PPV_ARGS(&_dxgiAdapter)),
		"GetParent failed to retrieve IDXGIAdapter.");

	ColdTableGraphicsLogThrowOnFail(_dxgiAdapter->GetParent(IID_PPV_ARGS(&_dxgiFactory)),
		"GetParent failed to retrieve IDXGIFactory.");

}

GraphicsDevice::~GraphicsDevice()
{ 
}

SwapChainPtr GraphicsDevice::CreateSwapChain(const SwapChainDesc& desc) const
{
	return std::make_shared<SwapChain>(desc, getGraphicsResourceDesc());
}

DeviceContextPtr GraphicsDevice::CreateDeviceContext()
{
	return std::make_shared<DeviceContext>(getGraphicsResourceDesc());
}

VertexBufferPtr GraphicsDevice::CreateVertexBuffer()
{
	VertexBufferDesc desc{{_logger},shared_from_this()};
	return std::make_shared<VertexBuffer>(desc);
}

ConstantBufferPtr GraphicsDevice::CreateConstantBuffer()
{
	ConstantBufferDesc desc{{_logger}, shared_from_this()};
	return std::make_shared<ConstantBuffer>(desc);
}

ShaderPtr GraphicsDevice::CreateShader(wchar_t* vertexShaderSrc, wchar_t* pixelShaderSrc)
{
	ShaderDesc desc{
		{_logger},
		shared_from_this(),
		vertexShaderSrc,
		pixelShaderSrc
	};
	return std::make_shared<Shader>(desc);
}

void GraphicsDevice::ExecuteCommandList(DeviceContext& context)
{
	Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
	ColdTableGraphicsLogThrowOnFail(context._context->FinishCommandList(false, &list),
		"FinishCommandList failed.");
	_d3dContext->ExecuteCommandList(list.Get(), false);
}

GraphicsResourceDesc GraphicsDevice::getGraphicsResourceDesc() const noexcept
{
	return {{_logger}, shared_from_this(),*_d3dDevice.Get(), *_dxgiFactory.Get()};
}
