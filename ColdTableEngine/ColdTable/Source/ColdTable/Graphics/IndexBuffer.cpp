#include <ColdTable/Graphics/IndexBuffer.h>

#include "GraphicsDevice.h"

ColdTable::IndexBuffer::IndexBuffer(const IndexBufferDesc& desc): Base(desc.base), _buffer(0), _listSize(0), _sourceDevice(desc.sourceDevice)
{}

ColdTable::IndexBuffer::~IndexBuffer()
{
	if (_buffer) _buffer->Release();
}

UINT ColdTable::IndexBuffer::GetListSize()
{
	return _listSize;
}

void ColdTable::IndexBuffer::LoadIndices(const void* list, UINT listSize)
{

	if (_buffer) _buffer->Release();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = 4 * listSize;
	bufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = list;

	_listSize = listSize;

	ColdTableGraphicsLogThrowOnFail(_sourceDevice->_d3dDevice->CreateBuffer(&bufferDesc, &initData, &_buffer),
		"CreateBuffer failed.");
}
