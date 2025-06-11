#include <ColdTable/Graphics/DeviceContext.h>

#include "EngineShader.h"
#include "IndexBuffer.h"
#include "SwapChain.h"
#include "ColdTable/Utility/ComputeShader.h"
#include <ColdTable/Resource/Texture/Texture.h>

#include "ColdTable/Resource/Material/Material.h"

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
	f32 colorArray[] = { (f32)color.x, (f32)color.y, (f32)color.z, (f32)color.w };
	auto renderTargetView = swapChain._renderTargetView.Get();
	_context->ClearRenderTargetView(renderTargetView, colorArray);
	_context->ClearDepthStencilView(swapChain._depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	_context->OMSetRenderTargets(1, &renderTargetView, swapChain._depthStencilView.Get());
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

void ColdTable::DeviceContext::BindTexture(TexturePtr texture)
{
	if (texture->_resourceView == nullptr) return;

	_context->VSSetShaderResources(0, 1, &texture->_resourceView);
	_context->PSSetShaderResources(0, 1, &texture->_resourceView);
}

void ColdTable::DeviceContext::BindVertexBuffer(VertexBufferPtr vertexBuffer)
{
	UINT stride = vertexBuffer->_vertexSize;
	UINT offset = 0;
	_context->IASetVertexBuffers(0, 1, &vertexBuffer->_buffer, &stride, &offset);
	_context->IASetInputLayout(vertexBuffer->_layout);
}

void ColdTable::DeviceContext::BindIndexBuffer(IndexBufferPtr indexBuffer)
{
	_context->IASetIndexBuffer(indexBuffer->_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void ColdTable::DeviceContext::UseShader(ShaderPtr shader)
{
	_context->VSSetShader(shader->_vertexShader, nullptr, 0);
	_context->PSSetShader(shader->_pixelShader, nullptr, 0);
}

void ColdTable::DeviceContext::BindConstantBuffer(ConstantBufferPtr constantBuffer, UINT bufferSlot)
{
	_context->VSSetConstantBuffers(bufferSlot, 1, &constantBuffer->_buffer);
	_context->PSSetConstantBuffers(bufferSlot, 1, &constantBuffer->_buffer);
	_context->CSSetConstantBuffers(bufferSlot, 1, &constantBuffer->_buffer);
}

void ColdTable::DeviceContext::BindComputeShader(ComputeShaderPtr computeShader)
{
	_context->CSSetShaderResources(0, 1, &computeShader->resourceView);
	_context->CSSetUnorderedAccessViews(0, 1, &computeShader->unorderedAccessView, nullptr);
	_context->CSSetShader(computeShader->_computeShader, nullptr, 0);
}

void ColdTable::DeviceContext::DispatchComputeShader(UINT xThreadGroups, UINT yThreadGroups, UINT zThreadGroups)
{
	_context->Dispatch(xThreadGroups, yThreadGroups, zThreadGroups);
}

void ColdTable::DeviceContext::Draw(RenderablePtr renderable)
{

	UseShader(renderable->_material->_shader);
	BindTexture(renderable->_material->_textures.at(0));

	BindVertexBuffer(renderable->_vertexBuffer);

	if (renderable->_indexBuffer != nullptr)
	{
		BindIndexBuffer(renderable->_indexBuffer);
		DrawIndexedTriangleList(renderable->_indexBuffer->GetListSize(), 0, 0);
		return;
	}

	switch (renderable->_drawMode)
	{
	case DRAWMODE_TRI:
		DrawTriangleList(renderable->_vertexBuffer->GetVertexCount(), 0);
		break;
	case DRAWMODE_TRI_STRIP:
		DrawTriangleStrip(renderable->_vertexBuffer->GetVertexCount(), 0);
		break;
	}
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

void ColdTable::DeviceContext::DrawIndexedTriangleList(UINT indexCount, UINT startVertexIndex, UINT startIndexIndex)
{
	_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	_context->DrawIndexed(indexCount, startIndexIndex, startVertexIndex);
}


