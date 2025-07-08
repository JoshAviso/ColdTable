#include <iostream>
#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

#include "../../../../../AboutScreen.h"
#include "ColdTable/Graphics/Camera.h"
#include "ColdTable/Graphics/IndexBuffer.h"
#include "ColdTable/Graphics/Renderables/Cube.h"
#include "ColdTable/Graphics/Renderables/Quad.h"
#include "ColdTable/Graphics/UIScreens/DemoScreen.h"
#include "ColdTable/Input/InputSystem.h"
#include "ColdTable/Utility/ComputeShader.h"
#include "ColdTable/Utility/Utils.h"

ColdTable::GameLoop::GameLoop(const GameDesc& desc):
	Base({desc.base}),
	tempWindowSize(desc.windowSize)
{
	Logger::Initialize(desc.logLevel);
	EngineTime::Initialize();
	InputSystem::Initialize();
	GraphicsEngine::Initialize(GraphicsEngineDesc{ desc.base });

	//_graphicsEngine = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{desc.base});
	_display = std::make_unique<Display>(DisplayDesc{desc.base,{desc.base, desc.windowSize}, GraphicsEngine::Instance->GetGraphicsDevice()});
	InputSystem::Instance->_windowPos = _display->WindowPosition();

	GraphicsEngine::Instance->SetViewportSize(desc.windowSize);

	_textureManager = new TextureManager();
	_meshManager = new MeshManager();

	ColdTableLogInfo("Game initialized.")
}

ColdTable::GameLoop::~GameLoop()
{
	free(_textureManager);
	free(_meshManager);
	ColdTableLogInfo("Game is shutting down.");
}

void ColdTable::GameLoop::onInternalStartup()
{
	tempShader = GraphicsEngine::Instance->CreateShader(L"VertexShader.hlsl", L"PixelShader.hlsl");

	TexturePtr woodTex =
		_textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\brick.png");

	MaterialPtr woodBox = GraphicsEngine::Instance->CreateMaterial(tempShader);
	woodBox->SetCullMode(CULL_MODE_BACK);
	woodBox->AddTexture(woodTex);

	/*
	// SLANTED CARDS
	// FIRST ROW
	for (int i = 0; i < 50; i++)
	{
		for (int j = 0; j < 50; j++)
		{
			
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 1.0f, 3.0f };
		cube->localRotation = { {0.0, 0.0, 1.0}, 70.0f };
		cube->localPosition = { ((float)i - 25) * 2.0f, 0.0f, ((float)j - 25) * 2.0f };
		}
	}
	for (int i = 0; i < 3; i++)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 0.01f, 3.0f };
		cube->localRotation = { {0.0, 0.0, -1.0}, 70.0f };
		cube->localPosition = { i * 3.4f + 1.7f, 0.0f, 0.0f };
	}
	// SECOND ROW
	for (int i = 0; i < 2; i++)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 0.01f, 3.0f };
		cube->localRotation = { {0.0, 0.0, 1.0}, 70.0f };
		cube->localPosition = { i * 3.4f + 1.7f, 4.8f, 0.0f };
	}
	for (int i = 0; i < 2; i++)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 0.01f, 3.0f };
		cube->localRotation = { {0.0, 0.0, -1.0}, 70.0f };
		cube->localPosition = { i * 3.4f + 3.4f, 4.8f, 0.0f };
	}
	// TOP
	for (int i = 0; i < 1; i++)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 0.01f, 3.0f };
		cube->localRotation = { {0.0, 0.0, 1.0}, 70.0f };
		cube->localPosition = { i * 3.4f + 3.4f, 9.6f, 0.0f };
	}
	for (int i = 0; i < 1; i++)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 0.01f, 3.0f };
		cube->localRotation = { {0.0, 0.0, -1.0}, 70.0f };
		cube->localPosition = { i * 3.4f + 5.1f, 9.6f, 0.0f };
	}

	// HORIZONTAL CARDS
	// BOTTOM ROW
	for (int i = 0; i < 2; i++)
	{
		CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
		GraphicsEngine::Instance->RegisterRenderable(cube);
		//cube->localScale = { 5.0f, 0.01f, 3.0f };
		cube->localPosition = { i * 3.4f + 2.5f, 2.4f, 0.0f };
	}
	*/
	// TOP ROW
	CubePtr cube = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
	GraphicsEngine::Instance->RegisterRenderable(cube);
	//cube->localScale = { 5.0f, 0.01f, 3.0f };
	cube->localPosition = {0.0f, 2.0f, 0.0f };

	CubePtr cube2 = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), tempShader);
	GraphicsEngine::Instance->RegisterRenderable(cube2);
	cube2->localScale = { 10.0f, 0.001f, 10.0f };
	//cube2->localPosition = { 4.5f, 7.2f, 0.0f };

	/*
	CubePtr cube2 = std::make_shared<Cube>(_graphicsEngine->CreateIndexBuffer(), tempShader);
	CubePtr cube3 = std::make_shared<Cube>(_graphicsEngine->CreateIndexBuffer(), tempShader);
	CubePtr cube4 = std::make_shared<Cube>(_graphicsEngine->CreateIndexBuffer(), tempShader);



	cube->localScale = {10.0f, 0.01f, 10.0f};
	cube2->localPosition = { 0.0f, 0.9f, 0.0f };
	cube3->localPosition = { -1.5f, 2.0f, 0.0f};
	cube4->localPosition = { -1.5f, 3.0f, -2.0f };

	_graphicsEngine->RegisterRenderable(cube2);
	_graphicsEngine->RegisterRenderable(cube3);
	_graphicsEngine->RegisterRenderable(cube4);
	*/

	MeshPtr teapot = _meshManager->CreateMeshFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Meshes\\teapot.obj", woodBox);
	//_graphicsEngine->RegisterMesh(teapot);

	LightSourceDesc dirLightDesc{
	};
	DirectionalLightPtr dirLight = std::make_shared<DirectionalLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(dirLight);
	dirLight->data.ambientIntensity = 0.7;
	dirLight->data.diffuseIntensity = 0.2;
	dirLight->direction = Vec3(0, -1, 1);
	dirLight->data.specIntensity = 0;
	dirLight->data.specPhong = 50;


	DirectionalLightPtr dirLight2 = std::make_shared<DirectionalLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(dirLight2);
	dirLight2->data.ambientColor = Vec3{0.0, 0.0, 1.0};
	dirLight2->data.diffuseColor = Vec3{ 0.0, 0.0, 1.0 };
	dirLight2->data.specColor = Vec3{ 0.0, 0.0, 1.0 };
	dirLight2->data.ambientIntensity = 0.0;
	dirLight2->data.diffuseIntensity = 0.0;
	dirLight2->direction = Vec3(-2, -2, 0);
	dirLight2->data.specIntensity = 0;
	dirLight2->data.specPhong = 5;
	dirLight2->tempRotAxis = Vec3(0.0, 1.0, 0.0);
	dirLight2->tempRotSpeed = 0.9f;

	SpotLightPtr spotlight = std::make_shared<SpotLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(spotlight);
	spotlight->data.diffuseColor = { 1.0, 0.0, 0.0};
	spotlight->data.ambientIntensity = 0.0;
	spotlight->data.diffuseIntensity = 0.0;
	spotlight->innerCutoff = 0.3;
	spotlight->outerCutoff = 0.5;
	spotlight->data.specIntensity = 0;
	spotlight->data.specPhong = 2;

	PointLightPtr pointlight = std::make_shared<PointLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(pointlight);
	pointlight->data.ambientColor = { 0.0, 1.0, 0.0 };
	pointlight->data.diffuseColor = { 0.0, 1.0, 0.0 };
	pointlight->data.specColor = { 0.0, 1.0, 0.0 };
	pointlight->data.ambientIntensity = 0.0;
	pointlight->data.diffuseIntensity = 0.0;
	pointlight->data.specIntensity = 0;
	pointlight->data.specPhong = 2;
	pointlight->position = Vec3(0.0,3.0, 0.0);

	LightConstantBufferContent constant{
		DirectionalLightContent{},
		DirectionalLightContent{},
		PointLightContent{},
		SpotLightContent{},
	};

	tempLightBuffer = GraphicsEngine::Instance->CreateConstantBuffer();
	tempLightBuffer->LoadData(&constant, sizeof(LightConstantBufferContent));

	PerObjectBufferContent objectBuffer{};
	tempObjectBuffer = GraphicsEngine::Instance->CreateConstantBuffer();
	tempObjectBuffer->LoadData(&objectBuffer, sizeof(PerObjectBufferContent));

	CameraBufferContent camBuffContent{};
	ConstantBufferPtr camBuff = GraphicsEngine::Instance->CreateConstantBuffer();
	camBuff->LoadData(&camBuff, sizeof(CameraBufferContent));
	CameraDesc camDesc{
		camBuff,
		tempWindowSize
	};
	tempCam = std::make_shared<Camera>(camDesc);

	tempCam->localPosition -= {0, 0, 1};

	tempCam->projectionMat =
		//Mat4::OrthoLH(20, 20, 0.1f, 20.0f);
		
		Mat4::PerspectiveFovLH(
			1.57f,
			tempWindowSize.width / tempWindowSize.height,
			0.1f, 100.0f
		);


	UIScreenPtr demoscreen = std::make_shared<DemoScreen>("Demo Screen 1");
	UIScreenPtr demoscreen2 = std::make_shared<DemoScreen>("Demo Screen 2");

	/*GraphicsEngine::Instance->RegisterUIScreen(demoscreen);
	GraphicsEngine::Instance->RegisterUIScreen(demoscreen2);*/

	GraphicsEngine::Instance->RegisterUIScreen(std::make_shared<AboutScreen>());


	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(_display->_windowHandle);
	ImGui_ImplDX11_Init(GraphicsEngine::Instance->_graphicsDevice->_d3dDevice.Get(), GraphicsEngine::Instance->_deviceContext->_context.Get());
	ImGui::StyleColorsDark();

	ImGuiStyle* style = &ImGui::GetStyle();
	style->Colors[ImGuiCol_WindowBg] = ImVec4(0, 0, 0, 1.f);
}

void ColdTable::GameLoop::onInternalCallback()
{
	InputSystem::Instance->_windowPos = _display->WindowPosition();

	GraphicsEngine::Instance->Render(tempCam, _display->GetSwapChain(), tempObjectBuffer, tempLightBuffer, tempWindowSize);

}