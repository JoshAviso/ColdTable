#include <iostream>
#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

#include "ColdTable/Graphics/IndexBuffer.h"
#include "ColdTable/Graphics/Renderables/Quad.h"
#include "ColdTable/Input/InputSystem.h"
#include "ColdTable/Utility/ComputeShader.h"
#include "ColdTable/Utility/Utils.h"

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
	InputSystem::Initialize();

	tempShader = _graphicsEngine->CreateShader(L"VertexShader.hlsl", L"PixelShader.hlsl");

	QuadDesc quad1 = {
		tempShader,
		{{-0.5, 0.5, 0.0}, {0.8, 0.8, 0.0}, { 0.8, 0.8, 0.0 }},
		{{0.5, 0.5, 0.0}, {0.0, 0.0, 0.8 }, { 0.8, 0.8, 0.8 }},
		{{0.5, -0.5, 0.0}, {0.8, 0.0, 0.0 }, { 0.0, 0.0, 0.8 }},
		{{-0.5, -0.5, 0.0}, {0.0, 0.8, 0.0 }, { 0.0, 0.0, 0.0 }},
	};
	tempQ1 = std::make_shared<Quad>(quad1);
	_graphicsEngine->RegisterRenderable(tempQ1);

	tempQ1->localRotation.rotate({0.0f, 1.0f, 0.0f}, 60.0f);

	Vertex vertlist[] = {
		// FRONT FACE
		Vertex({-0.5, -0.5, -0.5}, {1.0, 0.0, 0.0}),
		Vertex({-0.5,  0.5, -0.5}, {1.0, 1.0, 0.0}),
		Vertex({ 0.5,  0.5, -0.5}, {1.0, 1.0, 0.0}),
		Vertex({ 0.5, -0.5, -0.5}, {1.0, 0.0, 0.0}),
		//// BACK FACE
		Vertex({ 0.5, -0.5,  0.5}, {0.0, 1.0, 0.0}),
		Vertex({ 0.5,  0.5,  0.5}, {0.0, 1.0, 1.0}),
		Vertex({-0.5,  0.5,  0.5}, {0.0, 1.0, 1.0}),
		Vertex({-0.5, -0.5,  0.5}, {0.0, 1.0, 0.0})
	};

	unsigned int indexList[] = {
		0, 1, 2, 2, 3, 0, // FRONT
		4, 5, 6, 6, 7, 4, // BACK
		1, 6, 5, 5, 2, 1, // TOP
		7, 0, 3, 3, 4, 7, // BOTTOM
		3, 2, 5, 5, 4, 3, // RIGHT
		7, 6, 1, 1, 0, 7, // LEFT
	};

	IndexBufferPtr indexBuff = _graphicsEngine->CreateIndexBuffer();
	indexBuff->LoadIndices(indexList, ARRAYSIZE(indexList));

	RenderableDesc cubeDesc = {
		vertlist,
		ARRAYSIZE(vertlist),
		EGeometryDrawmode::DRAWMODE_TRI,
		tempShader
	};

	for (int i = 0; i < 1; i ++)
	{
		RenderablePtr cube = std::make_shared<Renderable>(cubeDesc);
		cube->LoadVerticesInIndex(vertlist, ARRAYSIZE(vertlist), indexBuff);
		_graphicsEngine->RegisterRenderable(cube);

		cube->localScale = Vec3(0.3f);
	}

	ConstantBufferContent constant{
		Mat4::Identity,
		Mat4::Identity,
		Mat4::Identity,
		0
	};

	tempConstantBuffer = _graphicsEngine->CreateConstantBuffer();
	tempConstantBuffer->LoadData(&constant, sizeof(ConstantBufferContent));

	//tempComputeShader = _graphicsEngine->CreateComputeShader(L"ComputeShader.hlsl", tempVertexArray);
}

void ColdTable::GameLoop::onInternalCallback()
{
	_graphicsEngine->Render(_display->GetSwapChain(), tempConstantBuffer, tempWindowSize);
}