#include <ColdTable/Graphics/DeviceContext.h>

#include "EngineShader.h"
#include "SwapChain.h"
#include "ColdTable/Utility/ComputeShader.h"

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

void ColdTable::DeviceContext::BindConstantBuffer(ConstantBufferPtr constantBuffer)
{
	_context->VSSetConstantBuffers(0, 1, &constantBuffer->_buffer);
	_context->PSSetConstantBuffers(0, 1, &constantBuffer->_buffer);
	_context->CSSetConstantBuffers(0, 1, &constantBuffer->_buffer);
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
	UseShader(renderable->_shader);
	BindVertexBuffer(renderable->_vertexBuffer);

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


