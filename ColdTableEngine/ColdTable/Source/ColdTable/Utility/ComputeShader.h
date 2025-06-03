#pragma once
#include <ColdTable/Core/Base.h>
#include <intsafe.h>
#define _WIN32_WINNT 0x600
#include <stdio.h>

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

namespace ColdTable
{
	
	class ComputeShader : public Base
	{
	public:
		explicit ComputeShader(const ComputeShaderDesc& desc);
		virtual ~ComputeShader();

		float* ReadBuffer();

	private:
		HRESULT CompileComputeShader(_In_ LPCWSTR srcFile, _In_ LPCSTR entryPoint,
			_In_ Microsoft::WRL::ComPtr<ID3D11Device> device, _Outptr_ ID3DBlob** blob);

	private:
		ID3D11Buffer* _stagingBuffer;
		ID3D11ComputeShader* _computeShader{};
		ID3D11ShaderResourceView* resourceView{};
		ID3D11UnorderedAccessView* unorderedAccessView{};
		ID3D11Buffer* inputBuffer;
		ID3D11Buffer* outputBuffer;

		Microsoft::WRL::ComPtr<ID3D11DeviceContext> _context;


		friend class DeviceContext;
		friend class GraphicsEngine;
	};
}

