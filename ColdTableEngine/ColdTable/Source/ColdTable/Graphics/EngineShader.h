#pragma once
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <d3d11.h>

namespace ColdTable
{
	class EngineShader
	{
	public:
		explicit EngineShader(ShaderDesc desc);
		virtual ~EngineShader();

	private:
		void GetBufferAndSize(void** shaderByteCode, UINT* shaderSize);

		ID3DBlob* _vertexShaderBlob;
		ID3DBlob* _pixelShaderBlob;

		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;

		GraphicsDevicePtr _sourceDevice{};

	private:
		friend class DeviceContext;
		friend class Renderable;
		friend class VertexBuffer;
	};
	
}

