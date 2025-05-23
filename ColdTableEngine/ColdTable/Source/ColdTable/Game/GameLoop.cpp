#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

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
	Vertex list[] = {
		{-0.5f, -0.5f, 0.0f,	-0.32f, -0.11f, 0.0f,	1.0f, 0.0f, 0.0f	,	0.0f, 1.0f, 0.0f},
		{-0.5f, 0.5f, 0.0f,	-0.11f, 0.78f, 0.0f,	0.0f, 1.0f, 0.0f	,	1.0f, 1.0f, 0.0f},
		{0.5f,	-0.5f, 0.0f,	0.75f, -0.73f, 0.0f,	0.0f, 0.0f, 1.0f	,	1.0f, 0.0f, 0.0f},
		{0.5f, 0.5f, 0.0f,		0.88f, 0.77f, 0.0f,	1.0f, 1.0f, 0.0f	,	0.0f, 0.0f, 1.0f}
	};

	UINT listSize = ARRAYSIZE(list);

	wchar_t vertexSource[] = L"VertexShader.hlsl";
	wchar_t pixelSource[] = L"PixelShader.hlsl";

	tempShader = _graphicsEngine->CreateShader(vertexSource, pixelSource);

	RenderableDesc desc = {
		{_logger},
		list,
		listSize,
		DRAWMODE_TRI_STRIP,
		tempShader,
	};
	tempRenderable = std::make_shared<Renderable>(desc);

	ConstantBufferContent constant;
	constant.m_time = 0;

	tempConstantBuffer = _graphicsEngine->CreateConstantBuffer();
	tempConstantBuffer->LoadData(&constant, sizeof(ConstantBufferContent));
}

void ColdTable::GameLoop::onInternalCallback()
{
	_graphicsEngine->Render(_display->GetSwapChain(), tempRenderable, tempConstantBuffer, tempWindowSize);

}