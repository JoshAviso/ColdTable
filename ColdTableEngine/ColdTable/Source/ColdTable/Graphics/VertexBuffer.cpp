#include <ColdTable/Graphics/VertexBuffer.h>

#include "GraphicsDevice.h"
#include "GraphicsLogUtil.h"

ColdTable::VertexBuffer::VertexBuffer(VertexBufferDesc desc): Base(desc.base), _buffer(0), _layout(0)
{
}

ColdTable::VertexBuffer::~VertexBuffer()
{
	if (_buffer)
	_buffer->Release();
	if (_layout)
	_layout->Release();
}

void ColdTable::VertexBuffer::LoadVertices(const void* list, UINT vertexSize, UINT listSize, ShaderPtr shader)
{
	if (_buffer) _buffer->Release();
	if (_layout) _layout->Release();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = vertexSize * listSize;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = list;

	_vertexSize = vertexSize;
	_listSize = listSize;

	ColdTableGraphicsLogThrowOnFail(shader->_sourceDevice->_d3dDevice->CreateBuffer(&bufferDesc, &initData, &_buffer),
		"CreateBuffer failed.");


	D3D11_INPUT_ELEMENT_DESC layout[] = 
	{
		{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD",0, DXGI_FORMAT_R32G32_FLOAT,0, 12,D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{"NORMAL",0, DXGI_FORMAT_R32G32B32_FLOAT,0, 20,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR",0, DXGI_FORMAT_R32G32B32_FLOAT,0, 32,D3D11_INPUT_PER_VERTEX_DATA, 0 },
		//{"COLOR",1, DXGI_FORMAT_R32G32B32_FLOAT,0, 24,D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	UINT layoutSize = ARRAYSIZE(layout);

	ColdTableGraphicsLogThrowOnFail(shader->_sourceDevice->_d3dDevice->CreateInputLayout(layout, layoutSize, shader->_vertexShaderBlob->GetBufferPointer(), shader->_vertexShaderBlob->GetBufferSize(), &_layout),
		"CreateInputLayer failed.")
}

UINT ColdTable::VertexBuffer::GetVertexCount()
{
	return _listSize;
}
