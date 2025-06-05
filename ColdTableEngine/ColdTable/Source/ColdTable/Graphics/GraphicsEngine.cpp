#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Graphics/GraphicsDevice.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Graphics/VertexBuffer.h>
#include <d3dcompiler.h>
#include <iostream>

#include "ColdTable/Math/Vertex.h"

ColdTable::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
	_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{desc.base});

	auto& device = *_graphicsDevice;
	_deviceContext = device.CreateDeviceContext();
}

ColdTable::GraphicsEngine::~GraphicsEngine()
{
}

void ColdTable::GraphicsEngine::RegisterRenderable(RenderablePtr renderable)
{
	_renderables.push_back(renderable);
}

void ColdTable::GraphicsEngine::UnregisterRenderable(RenderablePtr renderable)
{
	std::vector<RenderablePtr>::iterator index{};
	for (auto itr = _renderables.begin(); itr != _renderables.end(); ++itr)
	{
		if (*itr == renderable)
		{
			index = itr;
			break;
		}
	}

	if (index != _renderables.end())
		_renderables.erase(index);
}

void ColdTable::GraphicsEngine::RegisterComputeShader(ComputeShaderPtr computeShader)
{
	_deviceContext->BindComputeShader(computeShader);
}

ColdTable::GraphicsDevicePtr ColdTable::GraphicsEngine::GetGraphicsDevice() noexcept
{
	return _graphicsDevice;
}


void ColdTable::GraphicsEngine::TickConstantBuffer(ColdTable::ConstantBufferPtr constantBuffer, bool isDeferred)
{
	ConstantBufferContent constant;

	std::cout << runningTime << " " << animationTime << std::endl;

	if (transitioningToOriginalPosition)
		runningTime -= EngineTime::GetDeltaTime();
	else
		runningTime += EngineTime::GetDeltaTime();

	if (animationTime >= 2.0)
	{
		slowingDownAnim = true;
	}
	else if (animationTime <= 0.2)
		slowingDownAnim = false;

	if (runningTime >= animationTime)
	{
		transitioningToOriginalPosition = true;
		srand(time(0));
		//animationTime = static_cast<double>((rand() % (3 - 1 + 1)) + 1);
		//if (slowingDownAnim)
			//animationTime -= 0.2;
		//else
			//animationTime += 0.2;


		runningTime = animationTime;
		
	} else if (runningTime <= 0.0)
	{
		transitioningToOriginalPosition = false;
		srand(time(0));
		//animationTime = static_cast<double>((rand() % (3 - 1 + 1)) + 1);
		//if (slowingDownAnim)
			//animationTime -= 0.2;
		//else
			//animationTime += 0.2;
		runningTime = 0.0;
	}

	constant.m_time = static_cast<unsigned int>(runningTime / animationTime * 1000000.0);

	constantBuffer->Update(&*_deviceContext, &constant);
	_deviceContext->BindConstantBuffer(constantBuffer);
}

void ColdTable::GraphicsEngine::Render(SwapChain& swapChain, ConstantBufferPtr constantBuffer, Rect viewportSize)
{
	auto& context = *_deviceContext;
	context.ClearAndSetBackBuffer(swapChain, {0.2, 0.2, 0.5, 1});

	context.SetViewportSize(viewportSize);
	
	TickConstantBuffer(constantBuffer, true);
	
	for (auto renderable : _renderables)
	{
		context.Draw(renderable);
	}

	auto& device = *_graphicsDevice;
	device.ExecuteCommandList(context);

	swapChain.Present();
}

void ColdTable::GraphicsEngine::DispatchComputeShader(ComputeShaderPtr computeShader, UINT xThreads, UINT yThreads,
	UINT zThreads)
{
	/*D3D11_QUERY_DESC queryDesc{

	};
	_graphicsDevice->_d3dDevice->CreateQuery(&queryDesc, &_computeShaderQuery);
	_deviceContext->_context->Begin(_computeShaderQuery);*/

	_deviceContext->BindComputeShader(computeShader);
	_deviceContext->DispatchComputeShader(xThreads, yThreads, zThreads);
}

void ColdTable::GraphicsEngine::AwaitComputeShaderFinish()
{

}

void ColdTable::GraphicsEngine::SetViewportSize(Rect size)
{
	_deviceContext->SetViewportSize(size);
}

ColdTable::VertexBufferPtr ColdTable::GraphicsEngine::CreateVertexBuffer()
{
	return _graphicsDevice->CreateVertexBuffer();
}

ColdTable::ConstantBufferPtr ColdTable::GraphicsEngine::CreateConstantBuffer()
{
	return _graphicsDevice->CreateConstantBuffer();
}

ColdTable::ShaderPtr ColdTable::GraphicsEngine::CreateShader(const wchar_t* vertexShaderSrc, const wchar_t* pixelShaderSrc)
{
	return _graphicsDevice->CreateShader(vertexShaderSrc, pixelShaderSrc);
}

ColdTable::ComputeShaderPtr ColdTable::GraphicsEngine::CreateComputeShader(const wchar_t* sourceFile, const float* inputArray)
{
	return _graphicsDevice->CreateComputeShader(_deviceContext, sourceFile, inputArray);
}

void ColdTable::GraphicsEngine::BindComputeShader(ComputeShaderPtr computeShader)
{
	//_deviceContext->BindComputeShader(computeShader);
	_graphicsDevice->_d3dContext->CSSetShader(computeShader->_computeShader, nullptr, 0);

	_graphicsDevice->_d3dContext->CSSetShaderResources(0, 1, &computeShader->resourceView);
	_graphicsDevice->_d3dContext->CSSetUnorderedAccessViews(0, 1, &computeShader->unorderedAccessView, nullptr);
}

void ColdTable::GraphicsEngine::UseShader(const ShaderPtr& shader)
{
	//_deviceContext->UseShader(shader);
}
