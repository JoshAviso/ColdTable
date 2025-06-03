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
	tempShader = _graphicsEngine->CreateShader(L"VertexShader.hlsl", L"PixelShader.hlsl");

	QuadDesc quad1 = {
		tempShader,
		{{-0.75, 0.75, 0.0}, {0.8, 0.2, 0.2}},
		{{-0.15, 0.75, 0.0}, {0.2, 0.8, 0.2}},
		{{-0.15, 0.15, 0.0}, {0.2, 0.2, 0.8}},
		{{-0.75, 0.15, 0.0}, {0.8, 0.8, 0.2}},
	};
	QuadDesc quad2 = {
		tempShader,
		{{0.15, 0.75, 0.0}, {0.1, 0.1, 0.9}},
		{{0.75, 0.75, 0.0}, {0.1, 0.9, 0.9}},
		{{0.75, 0.15, 0.0}, {0.1, 0.9, 0.1}},
		{{0.15, 0.15, 0.0}, {0.9, 0.1, 0.1}}
	};
	QuadDesc quad3 = {
		tempShader,
		{{-0.5, -0.15, 0.0}, {1.0, 0.3, 0.3}},
		{{0.5, -0.15, 0.0}, {0.3, 0.3, 1.0}},
		{{0.5, -0.75, 0.0}, {1.0, 0.3, 1.0}},
		{{-0.5, -0.75, 0.0}, {0.3, 1.0, 0.3}}
	};
	tempQ1 = std::make_shared<Quad>(quad1);
	tempQ2 = std::make_shared<Quad>(quad2);
	tempQ3 = std::make_shared<Quad>(quad3);
	_graphicsEngine->RegisterRenderable(tempQ1);
	_graphicsEngine->RegisterRenderable(tempQ2);
	_graphicsEngine->RegisterRenderable(tempQ3);

	tempVertexArray[0] = quad1.vert1.position.x;
	tempVertexArray[1] = quad1.vert1.position.y;
	tempVertexArray[2] = quad1.vert1.position.z;
	tempVertexArray[3] = quad1.vert2.position.x;
	tempVertexArray[4] = quad1.vert2.position.y;
	tempVertexArray[5] = quad1.vert2.position.z;
	tempVertexArray[6] = quad1.vert3.position.x;
	tempVertexArray[7] = quad1.vert3.position.y;
	tempVertexArray[8] = quad1.vert3.position.z;
	tempVertexArray[9] = quad1.vert4.position.x;
	tempVertexArray[10] = quad1.vert4.position.y;
	tempVertexArray[11] = quad1.vert4.position.z;

	tempVertexArray[12] = quad2.vert1.position.x;
	tempVertexArray[13] = quad2.vert1.position.y;
	tempVertexArray[14] = quad2.vert1.position.z;
	tempVertexArray[15] = quad2.vert2.position.x;
	tempVertexArray[16] = quad2.vert2.position.y;
	tempVertexArray[17] = quad2.vert2.position.z;
	tempVertexArray[18] = quad2.vert3.position.x;
	tempVertexArray[19] = quad2.vert3.position.y;
	tempVertexArray[20] = quad2.vert3.position.z;
	tempVertexArray[21] = quad2.vert4.position.x;
	tempVertexArray[22] = quad2.vert4.position.y;
	tempVertexArray[23] = quad2.vert4.position.z;

	tempVertexArray[24] = quad3.vert1.position.x;
	tempVertexArray[25] = quad3.vert1.position.y;
	tempVertexArray[26] = quad3.vert1.position.z;
	tempVertexArray[27] = quad3.vert2.position.x;
	tempVertexArray[28] = quad3.vert2.position.y;
	tempVertexArray[29] = quad3.vert2.position.z;
	tempVertexArray[30] = quad3.vert3.position.x;
	tempVertexArray[31] = quad3.vert3.position.y;
	tempVertexArray[32] = quad3.vert3.position.z;
	tempVertexArray[33] = quad3.vert4.position.x;
	tempVertexArray[34] = quad3.vert4.position.y;
	tempVertexArray[35] = quad3.vert4.position.z;

	ConstantBufferContent constant;
	constant.m_time = 0;

	tempConstantBuffer = _graphicsEngine->CreateConstantBuffer();
	tempConstantBuffer->LoadData(&constant, sizeof(ConstantBufferContent));

	tempComputeShader = _graphicsEngine->CreateComputeShader(L"ComputeShader.hlsl", tempVertexArray);
}

void ColdTable::GameLoop::onInternalCallback()
{
	_graphicsEngine->BindComputeShader(tempComputeShader);
	_graphicsEngine->TickConstantBuffer(tempConstantBuffer, false);

	_graphicsEngine->DispatchComputeShader(tempComputeShader, 1, 1, 1);
	Sleep(5);

	// Update Vertex Positions
	float* array = tempComputeShader->ReadBuffer();
	Vertex vert1{ { array[0], array[1], array[2] } };
	Vertex vert2{ { array[3], array[4], array[5] } };
	Vertex vert3{ { array[6], array[7], array[8] } };
	Vertex vert4{ { array[9], array[10], array[11] } };
	Vertex vert5{ { array[12], array[13], array[14] } };
	Vertex vert6{ { array[15], array[16], array[17] } };
	Vertex vert7{ { array[18], array[19], array[20] } };
	Vertex vert8{ { array[21], array[22], array[23] } };
	Vertex vert9{ { array[24], array[25], array[26] } };
	Vertex vert10{ { array[27], array[28], array[29] } };
	Vertex vert11{ { array[30], array[31], array[32] } };
	Vertex vert12{ { array[33], array[34], array[35] } };
	Vertex list1[] = {vert1, vert2, vert4, vert3};
	Vertex list2[] = {vert5, vert6, vert8, vert7};
	Vertex list3[] = {vert9, vert10, vert12, vert11};
 	UINT listsize = ARRAYSIZE(list1);
	tempQ1->LoadVertices(list1, listsize);
	tempQ2->LoadVertices(list2, listsize);
	tempQ3->LoadVertices(list3, listsize); 

	_graphicsEngine->Render(_display->GetSwapChain(), tempConstantBuffer, tempWindowSize);
}