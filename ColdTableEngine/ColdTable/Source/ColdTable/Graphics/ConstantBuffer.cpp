#include "ConstantBuffer.h"

#include <ColdTable/Graphics/VertexBuffer.h>

#include <ColdTable/Graphics/GraphicsDevice.h>
#include <ColdTable/Graphics/GraphicsLogUtil.h>

ColdTable::ConstantBuffer::ConstantBuffer(ConstantBufferDesc desc) :
	Base(desc.base), _graphicsDevice(desc.graphicsDevice), _buffer(0), _bufferSize(desc.bufferSize)
{}

ColdTable::ConstantBuffer::~ConstantBuffer()
{
	if (_buffer) _buffer->Release();
}

void ColdTable::ConstantBuffer::LoadData(void* buffer)
{
	if (_buffer) _buffer->Release();

	D3D11_BUFFER_DESC bufferDesc{};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = _bufferSize;
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA initData{};
	initData.pSysMem = buffer;

	ColdTableGraphicsLogThrowOnFail(
		_graphicsDevice->_d3dDevice->CreateBuffer(&bufferDesc, &initData, &_buffer),
		"CreateBuffer failed.");

}

void ColdTable::ConstantBuffer::Update(DeviceContext* context, void* buffer)
{
	if (_buffer == nullptr) LoadData(buffer);

	context->_context->UpdateSubresource(this->_buffer, NULL, NULL, buffer, NULL, NULL);
}