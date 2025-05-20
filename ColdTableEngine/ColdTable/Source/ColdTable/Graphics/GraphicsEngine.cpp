#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Graphics/GraphicsDevice.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Graphics/VertexBuffer.h>
#include <d3dcompiler.h>

#include "ColdTable/Math/Vertex.h"

ColdTable::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{_logger});

	auto& device = *_graphicsDevice;
	_deviceContext = device.CreateDeviceContext();
}

ColdTable::GraphicsEngine::~GraphicsEngine()
{
}

ColdTable::GraphicsDevicePtr ColdTable::GraphicsEngine::GetGraphicsDevice() noexcept
{
	return _graphicsDevice;
}


void ColdTable::GraphicsEngine::Render(SwapChain& swapChain, VertexBufferPtr vertexBuffer, Rect viewportSize, ShaderPtr shader)
{
	auto& context = *_deviceContext;
	context.ClearAndSetBackBuffer(swapChain, {1, 0, 0, 1});

	context.SetViewportSize(viewportSize);
	UseShader(shader);
	context.BindVertexBuffer(vertexBuffer);
	context.DrawTriangles(vertexBuffer->GetVertexCount(), 0);

	auto& device = *_graphicsDevice;
	device.ExecuteCommandList(context);

	swapChain.Present();
}

void ColdTable::GraphicsEngine::SetViewportSize(Rect size)
{
	_deviceContext->SetViewportSize(size);
}

ColdTable::VertexBufferPtr ColdTable::GraphicsEngine::CreateVertexBuffer()
{
	return _graphicsDevice->CreateVertexBuffer();
}

ColdTable::ShaderPtr ColdTable::GraphicsEngine::CreateShader(wchar_t* vertexShaderSrc, wchar_t* pixelShaderSrc)
{
	return _graphicsDevice->CreateShader(vertexShaderSrc, pixelShaderSrc);
}

void ColdTable::GraphicsEngine::UseShader(const ShaderPtr& shader)
{
	_deviceContext->UseShader(shader);
}
