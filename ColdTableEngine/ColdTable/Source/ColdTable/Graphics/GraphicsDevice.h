#pragma once
#include <d3d11_4.h>
#include <wrl.h>

#include <ColdTable/Core/Common.h>
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Core.h>
#include <ColdTable/Graphics/GraphicsResource.h>
#include <ColdTable/Graphics/ConstantBuffer.h>
#include <ColdTable/Graphics/IndexBuffer.h>
#include <ColdTable/Graphics/GraphicsLogUtil.h>

#include <ColdTable/Graphics/SwapChain.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Graphics/EngineShader.h>
#include <ColdTable/Utility/ComputeShader.h>

namespace ColdTable
{
	class GraphicsDevice: public Base, public std::enable_shared_from_this<GraphicsDevice>
	{
	public:
		explicit GraphicsDevice(const GraphicsDeviceDesc& desc);
		virtual ~GraphicsDevice() override;

		SwapChainPtr CreateSwapChain(const SwapChainDesc& desc) const;
		DeviceContextPtr CreateDeviceContext();
		VertexBufferPtr CreateVertexBuffer();
		ConstantBufferPtr CreateConstantBuffer();
		IndexBufferPtr CreateIndexBuffer();
		ShaderPtr CreateShader(const wchar_t* vertexShaderSrc, const wchar_t* pixelShaderSrc);
		ComputeShaderPtr CreateComputeShader(DeviceContextPtr context, const wchar_t* sourceFile, const float* inputArray);

		void ExecuteCommandList(DeviceContext& context);

	private:
		GraphicsResourceDesc getGraphicsResourceDesc() const noexcept;

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> _d3dDevice{};
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _d3dContext{};
		Microsoft::WRL::ComPtr<IDXGIDevice> _dxgiDevice{};
		Microsoft::WRL::ComPtr<IDXGIAdapter> _dxgiAdapter{};
		Microsoft::WRL::ComPtr<IDXGIFactory> _dxgiFactory{};

	private:
		friend class VertexBuffer;
		friend class ConstantBuffer;
		friend class EngineShader;
		friend class ComputeShader;
		friend class GraphicsEngine;
		friend class IndexBuffer;
		friend class Texture;
	};
}

