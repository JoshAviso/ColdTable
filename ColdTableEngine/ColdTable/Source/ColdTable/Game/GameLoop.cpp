#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

#include "ColdTable/Graphics/Renderables/Quad.h"
#include "ColdTable/Utility/ComputeShader.h"

ColdTable::GameLoop::GameLoop(const GameDesc& desc):
	Base({desc.base}),
	tempWindowSize(desc.windowSize)
{
	Logger::Initialize(desc.logLevel);

	_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{desc.base});
	_display = std::make_unique<Display>(DisplayDesc{desc.base,{desc.base, desc.windowSize}, _graphicsEngine->GetGraphicsDevice()});

	_graphicsEngine->SetViewportSize(desc.windowSize);

	ColdTableLogInfo("Game initialized.")
}

ColdTable::GameLoop::~GameLoop()
{
	ColdTableLogInfo("Game is shutting down.");
}

void ColdTable::GameLoop::onInternalStartup()
{
	EngineTime::Initialize();

	tempShader = _graphicsEngine->CreateShader(L"VertexShader.hlsl", L"PixelShader.hlsl");

	QuadDesc quad1 = {
		tempShader,
		{{-0.2, -0.20, 0.0}, {-0.6, -0.9, 1.0}, {0.0, 0.8, 0.0 }, { 0.0, 0.0, 0.0 }},
		{{0.0, 0.75, 1.0}, {-0.9, 0.1, 1.0}, {0.8, 0.8, 0.0}, { 0.8, 0.8, 0.0 }},
		{{0.9, 0.75, 0.0}, {-0.6, -0.9, 0.0}, {0.0, 0.0, 0.8 }, { 0.8, 0.8, 0.8 }},
		{{0.1, -0.75, 1.0}, {1.0, -0.2, 1.0}, {0.8, 0.0, 0.0 }, { 0.0, 0.0, 0.8 }},
	};
	tempQ1 = std::make_shared<Quad>(quad1);
	_graphicsEngine->RegisterRenderable(tempQ1);

	ConstantBufferContent constant;
	constant.m_time = 0;

	tempConstantBuffer = _graphicsEngine->CreateConstantBuffer();
	tempConstantBuffer->LoadData(&constant, sizeof(ConstantBufferContent));

	//tempComputeShader = _graphicsEngine->CreateComputeShader(L"ComputeShader.hlsl", tempVertexArray);
}

void ColdTable::GameLoop::onInternalCallback()
{
	_graphicsEngine->Render(_display->GetSwapChain(), tempConstantBuffer, tempWindowSize);
}