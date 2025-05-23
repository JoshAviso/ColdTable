#include <ColdTable/Graphics/DeviceContext.h>

#include "Shader.h"
#include "SwapChain.h"

ColdTable::DeviceContext::DeviceContext(const GraphicsResourceDesc& desc): GraphicsResource(desc)
{
	ColdTableGraphicsLogThrowOnFail(_device.CreateDeferredContext(0, &_context),
		"CreateDeferredContext failed.")
}

ColdTable::DeviceContext::~DeviceContext()
{

}

void ColdTable::DeviceContext::ClearAndSetBackBuffer(const SwapChain& swapChain, const Vec4& color)
{
	f32 colorArray[] = { color.x, color.y, color.z, color.w };
	auto renderTargetView = swapChain._renderTargetView.Get();
	_context->ClearRenderTargetView(renderTargetView, colorArray);
	_context->OMSetRenderTargets(1, &renderTargetView, nullptr);
}

void ColdTable::DeviceContext::SetViewportSize(Rect size)
{
	D3D11_VIEWPORT viewport = {};
	viewport.TopLeftX = size.left;
	viewport.TopLeftY = size.top;
	viewport.Width = size.width;
	viewport.Height = size.height;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	_context->RSSetViewports(1, &viewport);
}

void ColdTable::DeviceContext::BindVertexBuffer(VertexBufferPtr vertexBuffer)
{
	UINT stride = vertexBuffer->_vertexSize;
	UINT offset = 0;
	_context->IASetVertexBuffers(0, 1, &vertexBuffer->_buffer, &stride, &offset);
	_context->IASetInputLayout(vertexBuffer->_layout);
}

void ColdTable::DeviceContext::UseShader(ShaderPtr shader)
{
	_context->VSSetShader(shader->_vertexShader, nullptr, 0);
	_context->PSSetShader(shader->_pixelShader, nullptr, 0);
}

void ColdTable::DeviceContext::BindConstantBuffer(ShaderPtr shader, ConstantBufferPtr constantBuffer)
{
	_context->VSSetConstantBuffers(0, 1, &constantBuffer->_buffer);
	_context->PSSetConstantBuffers(0, 1, &constantBuffer->_buffer);
}

void ColdTable::DeviceContext::DrawTriangleList(UINT vertexCount, UINT startVertexIndex)
{
	_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_context->Draw(vertexCount, startVertexIndex);
}

void ColdTable::DeviceContext::DrawTriangleStrip(UINT vertexCount, UINT startVertexIndex)
{
	_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	_context->Draw(vertexCount, startVertexIndex);
}


