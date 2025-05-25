#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

#include "ColdTable/Graphics/Renderables/Quad.h"

ColdTable::GameLoop::GameLoop(const GameDesc& desc):
	Base({*std::make_unique<Logger>(desc.logLevel).release()}),
	_loggerPtr(&_logger),
	tempWindowSize(desc.windowSize)
{
	_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{_logger});
	_display = std::make_unique<Display>(DisplayDesc{_logger, desc.windowSize, _graphicsEngine->GetGraphicsDevice()});

	_graphicsEngine->SetViewportSize(desc.windowSize);

	ColdTableLogInfo("Game initialized.")
}

ColdTable::GameLoop::~GameLoop()
{
	ColdTableLogInfo("Game is shutting down.");
}

void ColdTable::GameLoop::onInternalStartup()
{
	/*Vertex list[] = {
		{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f}},
		{{-0.5f, 0.5f, 0.0f},	{0.0f, 1.0f, 0.0f}},
		{{0.5f, 0.5f, 0.0f},	{1.0f, 1.0f, 0.0f}},
		{{0.5f,	-0.5f, 0.0f},	{0.0f, 0.0f, 1.0f}},
	};*/

	//UINT listSize = ARRAYSIZE(list);

	wchar_t vertexSource[] = L"VertexShader.hlsl";
	wchar_t pixelSource[] = L"PixelShader.hlsl";

	tempShader = _graphicsEngine->CreateShader(vertexSource, pixelSource);

	/*RenderableDesc desc = {
		{_logger},
		list,
		listSize,
		DRAWMODE_TRI_STRIP,
		tempShader,
	};*/

	QuadDesc desc1 = {
		{_logger},
		tempShader,
		{{-0.75, 0.75, 0.0}, {0.8, 0.2, 0.2}},
		{{-0.15, 0.75, 0.0}, {0.2, 0.8, 0.2}},
		{{-0.15, 0.15, 0.0}, {0.2, 0.2, 0.8}},
		{{-0.75, 0.15, 0.0}, {0.8, 0.8, 0.2}},
	};
	QuadDesc desc2 = {
		{_logger},
		tempShader,
		{{0.15, 0.75, 0.0}, {0.1, 0.1, 0.9}},
		{{0.75, 0.75, 0.0}, {0.1, 0.9, 0.9}},
		{{0.75, 0.15, 0.0}, {0.1, 0.9, 0.1}},
		{{0.15, 0.15, 0.0}, {0.9, 0.1, 0.1}}
	};
	QuadDesc desc3 = {
		{_logger},
		tempShader,
		{{-0.5, -0.15, 0.0}, {1.0, 0.3, 0.3}},
		{{0.5, -0.15, 0.0}, {0.3, 0.3, 1.0}},
		{{0.5, -0.75, 0.0}, {1.0, 0.3, 1.0}},
		{{-0.5, -0.75, 0.0}, {0.3, 1.0, 0.3}}
	};
	tempQuad1 = std::make_shared<Quad>(desc1);
	tempQuad2 = std::make_shared<Quad>(desc2);
	tempQuad3 = std::make_shared<Quad>(desc3);

	ConstantBufferContent constant;
	constant.m_time = 0;

	tempConstantBuffer = _graphicsEngine->CreateConstantBuffer();
	tempConstantBuffer->LoadData(&constant, sizeof(ConstantBufferContent));
}

void ColdTable::GameLoop::onInternalCallback()
{
	_graphicsEngine->Render(_display->GetSwapChain(), tempQuad1, tempQuad2, tempQuad3, tempConstantBuffer, tempWindowSize);
}