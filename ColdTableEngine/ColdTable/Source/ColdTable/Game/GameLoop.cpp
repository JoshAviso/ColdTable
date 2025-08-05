#include <iostream>
#include <ColdTable/Game/GameLoop.h>
#include <ColdTable/Window/Window.h>

#include <ColdTable/Core/Logger.h>
#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Game/Display.h>
#include <ColdTable/Math/Vertex.h>

#include <ColdTable/Resource/ShaderLibrary.h>

#include "ColdTable/ECS/Components/DebugBlurbComponent.h"
#include "ColdTable/ECS/Components/PhysicsComponent.h"
#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Editor/UIScreens/AboutScreen.h"
#include "ColdTable/Editor/UIScreens/DemoScreen.h"
#include "ColdTable/Graphics/Camera.h"
#include "ColdTable/Graphics/IndexBuffer.h"
#include "ColdTable/Graphics/Renderables/Cube.h"
#include "ColdTable/Graphics/Renderables/Quad.h"
#include "ColdTable/Input/InputSystem.h"
#include "ColdTable/Resource/Material/MaterialLibrary.h"
#include "ColdTable/Scenes/SceneManager.h"
#include "ColdTable/Utility/ComputeShader.h"
#include "ColdTable/Utility/Utils.h"

ColdTable::GameLoop::GameLoop(const GameDesc& desc):
	Base({desc.base}),
	tempWindowSize(desc.windowSize)
{
	Logger::Initialize(desc.logLevel);
	EngineTime::Initialize();
	InputSystem::Initialize();
	ActionManager::Initialize(32);
	GraphicsEngine::Initialize(GraphicsEngineDesc{ desc.base, desc.windowSize});
	InputSystem::Instance->_windowPos = GraphicsEngine::Instance->GetDisplay()->WindowPosition();

	GameObjectManager::Initialize();
	ECSEngine::Initialize();

	ShaderLibrary::Initialize();
	MaterialLibrary::Initialize();

	_textureManager = new TextureManager();
	MeshManager::Initialize();

	EditorUIManager::Initialize(GraphicsEngine::Instance->GetDisplay());

	SceneManager::Initialize();
	SceneManager::Instance->CreateScene("DefaultScene");

	ColdTableLogInfo("Game initialized.")
}

ColdTable::GameLoop::~GameLoop()
{
	free(_textureManager);
	ColdTableLogInfo("Game is shutting down.");
}

void ColdTable::GameLoop::onInternalStartup()
{

	ShaderPtr basicShader = ShaderLibrary::GetShader("BasicShader");
	ShaderPtr blankShader = ShaderLibrary::GetShader("BlankShader");
	MaterialPtr blankMat = MaterialLibrary::GetMaterial("Default");

	TexturePtr brickTex = _textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\brick.png");
	TexturePtr woodTex = _textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\wood.jpg");
	TexturePtr grassTex = _textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\grass.jpg");
	TexturePtr groundTex = _textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\ground.jpg");
	TexturePtr sandTex = _textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\sand.jpg");

	MaterialPtr brickMat = MaterialLibrary::CreateMaterial("Brick", basicShader, brickTex, CULL_MODE_BACK);
	MaterialPtr woodMat = MaterialLibrary::CreateMaterial("Wood", basicShader, woodTex, CULL_MODE_BACK);
	MaterialPtr grassMat = MaterialLibrary::CreateMaterial("Grass", basicShader, grassTex, CULL_MODE_BACK);
	MaterialPtr groundMat = MaterialLibrary::CreateMaterial("Dirt", basicShader, groundTex, CULL_MODE_BACK);
	MaterialPtr sandMat = MaterialLibrary::CreateMaterial("Sand", basicShader, sandTex, CULL_MODE_BACK);

	MeshManager::Instance->CreateMeshFromFile("Bunny", GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Meshes\\bunny.obj", blankMat);
	MeshManager::Instance->CreateMeshFromFile("Armadillo", GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Meshes\\armadillo.obj", blankMat);
	MeshManager::Instance->CreateMeshFromFile("Lucy", GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Meshes\\lucy.obj", blankMat);
	MeshManager::Instance->CreateMeshFromFile("Teapot", GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Meshes\\teapot.obj", blankMat);

	/*
	GameObjectPtr planeObj = GameObjectManager::CreateGameObject("Plane");
	PhysicsComponent* planeRB = planeObj->AddComponent<PhysicsComponent>(0.0f);
	planeRB->_bodyType = BodyType::STATIC;

	planeObj->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Plane"));
	planeObj->AddComponent<MaterialComponent>();

	for (int i = 0; i < 20; i ++)
	{
		GameObjectPtr cubeObject = GameObjectManager::CreateGameObject("Cube (" + std::to_string(i) + ")");
		cubeObject->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Cube"));
		cubeObject->transform->position.y = 10.0f;
		PhysicsComponent* rb = cubeObject->AddComponent<PhysicsComponent>(1.0f);
		rb->_rigidBody->enableGravity(true);


		if (i % 2 == 0)	cubeObject->AddComponent<MaterialComponent>(brickMat);
		else			cubeObject->AddComponent<MaterialComponent>(woodMat);
	}
	*/

	LightSourceDesc dirLightDesc{};
	DirectionalLightPtr dirLight = std::make_shared<DirectionalLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(dirLight);
	dirLight->ambientIntensity = 0.7;
	dirLight->diffuseIntensity = 0.2;
	dirLight->direction = Vec3(0, -1, 1);
	dirLight->specIntensity = 0;
	dirLight->specPhong = 50;


	DirectionalLightPtr dirLight2 = std::make_shared<DirectionalLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(dirLight2);
	dirLight2->ambientColor = Vec3{0.0, 0.0, 1.0};
	dirLight2->diffuseColor = Vec3{ 0.0, 0.0, 1.0 };
	dirLight2->specColor = Vec3{ 0.0, 0.0, 1.0 };
	dirLight2->ambientIntensity = 0.0;
	dirLight2->diffuseIntensity = 0.0;
	dirLight2->direction = Vec3(-2, -2, 0);
	dirLight2->specIntensity = 0;
	dirLight2->specPhong = 5;
	dirLight2->tempRotAxis = Vec3(0.0, 1.0, 0.0);
	dirLight2->tempRotSpeed = 0.9f;

	SpotLightPtr spotlight = std::make_shared<SpotLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(spotlight);
	spotlight->diffuseColor = { 1.0, 0.0, 0.0};
	spotlight->ambientIntensity = 0.0;
	spotlight->diffuseIntensity = 0.0;
	spotlight->innerCutoff = 0.3;
	spotlight->outerCutoff = 0.5;
	spotlight->specIntensity = 0;
	spotlight->specPhong = 2;

	PointLightPtr pointlight = std::make_shared<PointLight>(dirLightDesc);
	GraphicsEngine::Instance->RegisterLight(pointlight);
	pointlight->ambientColor = { 0.0, 1.0, 0.0 };
	pointlight->diffuseColor = { 0.0, 1.0, 0.0 };
	pointlight->specColor = { 0.0, 1.0, 0.0 };
	pointlight->ambientIntensity = 0.0;
	pointlight->diffuseIntensity = 0.0;
	pointlight->specIntensity = 0;
	pointlight->specPhong = 2;
	pointlight->position = Vec3(0.0,3.0, 0.0);


	tempCam = std::make_shared<Camera>(CameraDesc{tempWindowSize});
	tempCam->localPosition -= {0, 0, 1};
	tempCam->projectionMat =
		//Mat4::OrthoLH(20, 20, 0.1f, 20.0f);
		
		Mat4::PerspectiveFovLH(
			1.57f,
			tempWindowSize.width / tempWindowSize.height,
			0.1f, 100.0f
		);
	//tempCam->targetMesh = teapot;

	GraphicsEngine::Instance->RegisterCamera(tempCam);

	TexturePtr logoTex = _textureManager->CreateTextureFromFile(GraphicsEngine::Instance->_graphicsDevice, L"Assets\\Textures\\DLSULogo.png");
	dynamic_cast<AboutScreen*>(EditorUIManager::GetScreen("Credits").get())->SetLogo(logoTex);
	
}

void ColdTable::GameLoop::onInternalCallback()
{
	InputSystem::Instance->_windowPos = GraphicsEngine::Instance->GetDisplay()->WindowPosition();
	GraphicsEngine::Instance->Render();

}