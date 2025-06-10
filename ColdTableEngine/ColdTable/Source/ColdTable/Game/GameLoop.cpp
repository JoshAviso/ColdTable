#include <iostream>
#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

#include "ColdTable/Graphics/Camera.h"
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

	_textureManager = new TextureManager();

	ColdTableLogInfo("Game initialized.")
}

ColdTable::GameLoop::~GameLoop()
{
	free(_textureManager);
	ColdTableLogInfo("Game is shutting down.");
}

void ColdTable::GameLoop::onInternalStartup()
{
	EngineTime::Initialize();
	InputSystem::Initialize();

	TexturePtr woodTex =
		_textureManager->CreateTextureFromFile(_graphicsEngine->_graphicsDevice, L"Assets\\Textures\\wood.jpg");

	tempShader = _graphicsEngine->CreateShader(L"VertexShader.hlsl", L"PixelShader.hlsl");

	MaterialPtr woodBox = _graphicsEngine->CreateMaterial(tempShader);
	woodBox->SetCullMode(CULL_MODE_BACK);
	woodBox->AddTexture(woodTex);

	/*QuadDesc quad1 = {
		tempShader,
		{{-0.5, 0.5, 0.0}, {0.8, 0.8, 0.0}, { 0.8, 0.8, 0.0 }},
		{{0.5, 0.5, 0.0}, {0.0, 0.0, 0.8 }, { 0.8, 0.8, 0.8 }},
		{{0.5, -0.5, 0.0}, {0.8, 0.0, 0.0 }, { 0.0, 0.0, 0.8 }},
		{{-0.5, -0.5, 0.0}, {0.0, 0.8, 0.0 }, { 0.0, 0.0, 0.0 }},
	};
	tempQ1 = std::make_shared<Quad>(quad1);
	_graphicsEngine->RegisterRenderable(tempQ1);

	tempQ1->localRotation.rotate({0.0f, 1.0f, 0.0f}, 60.0f);*/

	Vec3 positionList[] = {
		// FRONT FACE
		{-0.5, -0.5, -0.5},
		{-0.5,  0.5, -0.5},
		{ 0.5,  0.5, -0.5},
		{ 0.5, -0.5, -0.5},
		//// BACK FACE
		{ 0.5, -0.5,  0.5},
		{ 0.5,  0.5,  0.5},
		{-0.5,  0.5,  0.5},
		{-0.5, -0.5,  0.5}
	};
	Vec3 normalList[] = {
		{0.0f, 0.0f, -1.0f},
		{0.0f, 0.0f, 1.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{1.0f, 0.0f, 0.0f},
		{-1.0f, 0.0f, 0.0f},
	};
	Vec2 texcoordList[] = {
		{0.0f, 0.0f},
		{0.0f, 1.0f},
		{1.0f, 0.0f},
		{1.0f, 1.0f}
	};
	Vertex vertlist[] = {

		//
		{positionList[0], texcoordList[1], normalList[0]},
		{positionList[1], texcoordList[0], normalList[0]},
		{positionList[2], texcoordList[2], normalList[0]},
		{positionList[3], texcoordList[3], normalList[0]},
		// FRONT
		//
		{positionList[4], texcoordList[1], normalList[1]},
		{positionList[5], texcoordList[0], normalList[1]},
		{positionList[6], texcoordList[2], normalList[1]},
		{positionList[7], texcoordList[3], normalList[1]},
		// BACK
		//
		{positionList[1], texcoordList[1], normalList[2]},
		{positionList[6], texcoordList[0], normalList[2]},
		{positionList[5], texcoordList[2], normalList[2]},
		{positionList[2], texcoordList[3], normalList[2]},
		// TOP
		//
		{positionList[7], texcoordList[1], normalList[3]},
		{positionList[0], texcoordList[0], normalList[3]},
		{positionList[3], texcoordList[2], normalList[3]},
		{positionList[4], texcoordList[3], normalList[3]},
		// BOTTOM
		//
		{positionList[3], texcoordList[1], normalList[4]},
		{positionList[2], texcoordList[0], normalList[4]},
		{positionList[5], texcoordList[2], normalList[4]},
		{positionList[4], texcoordList[3], normalList[4]},
		// RIGHT
		//
		{positionList[7], texcoordList[1], normalList[5]},
		{positionList[6], texcoordList[0], normalList[5]},
		{positionList[1], texcoordList[2], normalList[5]},
		{positionList[0], texcoordList[3], normalList[5]},
		// LEFT
	};

	unsigned int indexList[] = {
		0, 1, 2, 2, 3, 0, // FRONT
		4, 5, 6, 6, 7, 4, // BACK
		8, 9, 10, 10, 11, 8, // TOP
		12, 13, 14, 14, 15, 12, // BOTTOM
		16, 17, 18, 18, 19, 16, // RIGHT
		20, 21, 22, 22, 23, 20, // LEFT
	};

	IndexBufferPtr indexBuff = _graphicsEngine->CreateIndexBuffer();
	indexBuff->LoadIndices(indexList, ARRAYSIZE(indexList));

	RenderableDesc cubeDesc = {
		vertlist,
		ARRAYSIZE(vertlist),
		EGeometryDrawmode::DRAWMODE_TRI,
		woodBox
	};

	RenderablePtr cube = std::make_shared<Renderable>(cubeDesc);
	cube->LoadVerticesInIndex(vertlist, ARRAYSIZE(vertlist), indexBuff);
	_graphicsEngine->RegisterRenderable(cube);
	cube->localPosition = {1, 0, 0};

	RenderablePtr cube2 = std::make_shared<Renderable>(cubeDesc);
	cube2->LoadVerticesInIndex(vertlist, ARRAYSIZE(vertlist), indexBuff);
	_graphicsEngine->RegisterRenderable(cube2);
	cube2->localPosition = { -3, 0, 0 };

	RenderablePtr cube3 = std::make_shared<Renderable>(cubeDesc);
	cube3->LoadVerticesInIndex(vertlist, ARRAYSIZE(vertlist), indexBuff);
	_graphicsEngine->RegisterRenderable(cube3);
	cube3->localPosition = { 0, 0, 4};

	RenderablePtr cube4 = std::make_shared<Renderable>(cubeDesc);
	cube4->LoadVerticesInIndex(vertlist, ARRAYSIZE(vertlist), indexBuff);
	_graphicsEngine->RegisterRenderable(cube4);
	cube4->localPosition = { 0, 0, -2 };

	LightSourceDesc dirLightDesc{
	};
	DirectionalLightPtr dirLight = std::make_shared<DirectionalLight>(dirLightDesc);
	_graphicsEngine->RegisterLight(dirLight);
	dirLight->data.ambientIntensity = 0.5;
	dirLight->data.diffuseIntensity = 0.5;
	dirLight->direction = Vec3(0, -1, 0);
	dirLight->data.specIntensity = 50;
	dirLight->data.specPhong = 50;


	DirectionalLightPtr dirLight2 = std::make_shared<DirectionalLight>(dirLightDesc);
	_graphicsEngine->RegisterLight(dirLight2);
	dirLight2->data.ambientColor = Vec3{0.0, 0.0, 1.0};
	dirLight2->data.diffuseColor = Vec3{ 0.0, 0.0, 1.0 };
	dirLight2->data.specColor = Vec3{ 0.0, 0.0, 1.0 };
	dirLight2->data.ambientIntensity = 0.4;
	dirLight2->data.diffuseIntensity = 0.8;
	dirLight2->direction = Vec3(-2, -2, 0);
	dirLight2->data.specIntensity = 1;
	dirLight2->data.specPhong = 5;
	dirLight2->tempRotAxis = Vec3(0.0, 1.0, 0.0);
	dirLight2->tempRotSpeed = 0.9f;

	SpotLightPtr spotlight = std::make_shared<SpotLight>(dirLightDesc);
	_graphicsEngine->RegisterLight(spotlight);
	spotlight->data.diffuseColor = { 1.0, 0.0, 0.0};
	spotlight->data.ambientIntensity = 1.0;
	spotlight->data.diffuseIntensity = 10.0;
	spotlight->innerCutoff = 0.3;
	spotlight->outerCutoff = 0.5;
	spotlight->data.specIntensity = 1;
	spotlight->data.specPhong = 2;

	PointLightPtr pointlight = std::make_shared<PointLight>(dirLightDesc);
	_graphicsEngine->RegisterLight(pointlight);
	pointlight->data.ambientColor = { 0.0, 1.0, 0.0 };
	pointlight->data.diffuseColor = { 0.0, 1.0, 0.0 };
	pointlight->data.specColor = { 0.0, 1.0, 0.0 };
	pointlight->data.ambientIntensity = 2.0;
	pointlight->data.diffuseIntensity = 10.0;
	pointlight->data.specIntensity = 1;
	pointlight->data.specPhong = 2;
	pointlight->position = Vec3(0.0,3.0, 0.0);

	LightConstantBufferContent constant{
		DirectionalLightContent{},
		DirectionalLightContent{},
		PointLightContent{},
		SpotLightContent{},
	};

	tempLightBuffer = _graphicsEngine->CreateConstantBuffer();
	tempLightBuffer->LoadData(&constant, sizeof(LightConstantBufferContent));


	CameraBufferContent camBuffContent{};
	ConstantBufferPtr camBuff = _graphicsEngine->CreateConstantBuffer();
	camBuff->LoadData(&camBuff, sizeof(CameraBufferContent));
	CameraDesc camDesc{
		camBuff
	};
	tempCam = std::make_shared<Camera>(camDesc);

	tempCam->localPosition -= {0, 0, 1};

	tempCam->projectionMat =
		Mat4::PerspectiveFovLH(
			1.57f,
			tempWindowSize.width / tempWindowSize.height,
			0.1f, 100.0f
		);
}

void ColdTable::GameLoop::onInternalCallback()
{
	_graphicsEngine->Render(tempCam, _display->GetSwapChain(), tempLightBuffer, tempWindowSize);
}