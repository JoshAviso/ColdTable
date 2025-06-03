#include <ColdTable/Graphics/EngineShader.h>

#include "GraphicsDevice.h"

ColdTable::EngineShader::EngineShader(ShaderDesc desc): _sourceDevice(desc.sourceDevice)
{
	ID3DBlob* errblob = nullptr;
	D3DCompileFromFile(desc.vertexShaderSourceFile, nullptr, nullptr, "vsmain", "vs_5_0", NULL, NULL, &_vertexShaderBlob, &errblob);
	D3DCompileFromFile(desc.pixelShaderSourceFile, nullptr, nullptr, "psmain", "ps_5_0", NULL, NULL, &_pixelShaderBlob, &errblob);
	_sourceDevice->_d3dDevice->CreateVertexShader(_vertexShaderBlob->GetBufferPointer(), _vertexShaderBlob->GetBufferSize(), nullptr, &_vertexShader);
	_sourceDevice->_d3dDevice->CreatePixelShader(_pixelShaderBlob->GetBufferPointer(), _pixelShaderBlob->GetBufferSize(), nullptr, &_pixelShader);

}

ColdTable::EngineShader::~EngineShader()
{
	_vertexShader->Release();
	_vertexShaderBlob->Release();
	_pixelShader->Release();
	_pixelShaderBlob->Release();
}

void ColdTable::EngineShader::GetBufferAndSize(void** shaderByteCode, UINT* shaderSize)
{
	*shaderByteCode = _vertexShaderBlob->GetBufferPointer();
	*shaderSize = (UINT)_vertexShaderBlob->GetBufferSize();
}
