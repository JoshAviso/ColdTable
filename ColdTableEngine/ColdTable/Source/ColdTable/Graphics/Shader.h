#pragma once
#include <ColdTable/Core/Base.h>
#include <ColdTable/Core/Common.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <d3d11.h>

namespace ColdTable
{
	class Shader: public Base
	{
	public:
		explicit Shader(ShaderDesc desc);
		virtual ~Shader();

	public:
		void GetBufferAndSize(void** shaderByteCode, UINT* shaderSize);

	private:
		ID3DBlob* _vertexShaderBlob;
		ID3DBlob* _pixelShaderBlob;

		ID3D11VertexShader* _vertexShader;
		ID3D11PixelShader* _pixelShader;

	private:
		friend class DeviceContext;
	};
	
}

