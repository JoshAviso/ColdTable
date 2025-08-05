#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Graphics/GraphicsDevice.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Graphics/VertexBuffer.h>
#include <ColdTable/Editor/UIScreens/IUIScreen.h>
#include <d3dcompiler.h>
#include <iostream>

#include "Camera.h"
#include <ColdTable/Resource/ShaderLibrary.h>
#include "ColdTable/ECS/Components/MaterialComponent.h"
#include "ColdTable/ECS/Components/MeshComponent.h"
#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Math/Vertex.h"
#include "ColdTable/Editor/VertexObject.h"
#include "ColdTable/Editor/UIScreens/MainMenuUI.h"
#include "ColdTable/Resource/Mesh/Mesh.h"
#include "ColdTable/Utility/Utils.h"
#include "DearImGUI/imgui.h"
#include "DearImGUI/imgui_impl_dx11.h"
#include "DearImGUI/imgui_impl_win32.h"
#include "Renderables/Cube.h"

ColdTable::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc):
	Base(desc.base), _windowSize(desc.windowSize)
{
	// Device and Context Setup
	_graphicsDevice = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{desc.base});
	_deviceContext = _graphicsDevice->CreateDeviceContext();

	// Display Setup
	_display = std::make_unique<Display>(DisplayDesc{ desc.base,{desc.base, desc.windowSize}, _graphicsDevice});
	_deviceContext->SetViewportSize(desc.windowSize);

	// Buffer Setup
	_lightingBuffer = _graphicsDevice->CreateConstantBuffer(sizeof(LightConstantBufferContent));
	_objectBuffer = _graphicsDevice->CreateConstantBuffer(sizeof(PerObjectBufferContent));
	_cameraBuffer = _graphicsDevice->CreateConstantBuffer(sizeof(CameraBufferContent));
}

ColdTable::GraphicsEngine::~GraphicsEngine()
{
}

ColdTable::GraphicsEngine* ColdTable::GraphicsEngine::Instance = nullptr;
void ColdTable::GraphicsEngine::Initialize(const GraphicsEngineDesc& desc)
{
	if (Instance == nullptr)
		Instance = new GraphicsEngine(desc);
}


ColdTable::IEditorPickablePtr ColdTable::GraphicsEngine::CheckHitObject(Ray ray)
{
	IEditorPickablePtr _hit = nullptr;
	closestDist = 1000000.0f;

	// Check Objects
	for (GameObjectPtr gameObject : GameObjectManager::Instance->_registeredObjects)
	{
		float dist;
		auto renderable = gameObject->renderable;
		Mat4 transform = gameObject->transform->transformMat();
		if (_pickupMode != EPickableType::PickupVertex)
		{
			if (ray.TestIntersection(gameObject, dist))
			{
				if (dist < closestDist && _pickupMode == EPickableType::PickupObject)
				{
					closestDist = dist;
					_hit = gameObject;
				}
				if (_pickupMode == EPickableType::PickupObject) continue;


				// Check Faces
				for (auto face : renderable->_vertexBuffer->_faceObjects)
				{
					if (ray.TestIntersection(face, transform, dist))
					{
						if (dist < closestDist && _pickupMode == EPickableType::PickupFace)
						{
							closestDist = dist;
							_hit = face;
						}
						if (_pickupMode == EPickableType::PickupFace) continue;

						// Check Edges
						for (auto edge : face->_edges)
						{
							if (ray.TestIntersection(edge, transform, dist))
							{
								if (dist < closestDist && _pickupMode == EPickableType::PickupEdge)
								{
									closestDist = dist;
									_hit = edge;
								}

							}
						}
					}
				}
			}
		}
		// Check Vertices
		if (_pickupMode == EPickableType::PickupVertex)
		{
			for (auto vertObj : renderable->_vertexBuffer->_vertexObjects)
			{
				if (ray.TestIntersection(vertObj, transform, dist))
				{
					if (dist < closestDist)
					{
						closestDist = dist;
						_hit = vertObj;
					}
				}
			}
		}
	}
	return _hit;
}

void ColdTable::GraphicsEngine::SetPickupMode(EPickableType mode)
{
	_pickupMode = mode;
}

void ColdTable::GraphicsEngine::RegisterCamera(CameraPtr camera)
{
	_cameras.push_back(camera);
}

void ColdTable::GraphicsEngine::UnregisterCamera(CameraPtr camera)
{
	std::vector<CameraPtr>::iterator index{};
	for (auto itr = _cameras.begin(); itr != _cameras.end(); ++itr)
	{
		if (*itr == camera)
		{
			index = itr;
			break;
		}
	}
	if (index != _cameras.end())
		_cameras.erase(index);
}

void ColdTable::GraphicsEngine::RegisterLight(const LightSourcePtr& light)
{
	_lights.push_back(light);
}

void ColdTable::GraphicsEngine::UnregisterLight(const LightSourcePtr& light)
{
	std::vector<LightSourcePtr>::iterator index{};
	for (auto itr = _lights.begin(); itr != _lights.end(); ++itr)
	{
		if (*itr == light)
		{
			index = itr;
			break;
		}
	}

	if (index != _lights.end())
		_lights.erase(index);
}

void ColdTable::GraphicsEngine::RegisterComputeShader(ComputeShaderPtr computeShader)
{
	_deviceContext->BindComputeShader(computeShader);
}

ColdTable::GraphicsDevicePtr ColdTable::GraphicsEngine::GetGraphicsDevice() noexcept
{
	return _graphicsDevice;
}

void ColdTable::GraphicsEngine::Render()
{
	if (_cameras.empty()) return;

	_deviceContext->ClearAndSetBackBuffer(_display->GetSwapChain(), {0.2, 0.2, 0.5, 1});
	_deviceContext->SetViewportSize(_windowSize);

	PassPerFrameConstantBuffers();
	RenderObjects();
	RenderUI();
	
	auto& device = *_graphicsDevice;
	device.ExecuteCommandList(*(_deviceContext.get()));
	
	_display->GetSwapChain().Present();
}

void ColdTable::GraphicsEngine::PassPerFrameConstantBuffers()
{
	std::vector<ComponentPtr> lights = ECSEngine::GetInstance()->GetComponents(EComponentType::Light);


	LightConstantBufferContent lightBufferContent{};
	for (int i = 0; i < 32; i++)
	{
		if (i < _lights.size())
		{
			//LightComponentPtr light = std::dynamic_pointer_cast<LightComponent>(lights[i]);
			lightBufferContent.lights[i] = _lights[i]->GenerateLightData();
		}
		else lightBufferContent.lights[i] = LightContent{};
	}

	_lightingBuffer->Update(_deviceContext.get(), &lightBufferContent);
	_deviceContext->BindConstantBuffer(_lightingBuffer, 0);

	CameraBufferContent camBuffer{
		ActiveCamera()->viewMatrix(),
		ActiveCamera()->projectionMat,
		ActiveCamera()->localPosition
	};
	_cameraBuffer->Update(_deviceContext.get(), &camBuffer);
	_deviceContext->BindConstantBuffer(_cameraBuffer, 1);
}

void ColdTable::GraphicsEngine::RenderObjects()
{
	// Draw Game Objects
	if (GameObjectManager::Instance != nullptr)
	{
		for (const GameObjectPtr& gameObject : GameObjectManager::Instance->_registeredObjects)
		{
			if (!gameObject->enabled) continue;

			auto meshes = gameObject->GetComponents<MeshComponent>();
			auto materials = gameObject->GetComponents<MaterialComponent>();

			for (int i = 0; i < meshes.size(); i++)
			{
				if (!meshes[i]->enabled) continue;

				MaterialComponentPtr material = nullptr;
				if (i < materials.size() && materials[i]->enabled) material = materials[i];

				PerObjectBufferContent objectBuffer = {
					gameObject->transform->transformMat(),
					material == nullptr ?
						Vec3(1.0, 1.0, 1.0) :
						material->_material->tint,
					material != nullptr
				};

				_objectBuffer->Update(&*_deviceContext, &objectBuffer);
				_deviceContext->BindConstantBuffer(_objectBuffer, 2);

				_deviceContext->Draw(meshes[i], material);
			}
		}
	}
}

void ColdTable::GraphicsEngine::RenderUI()
{
	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX11_NewFrame();
	ImGui::NewFrame();

	MainMenuUI::DrawUI();
	for (auto uiScreen : EditorUIManager::Instance->_screenList)
	{
		if (!uiScreen->ShowScreen) continue;

		ImGui::Begin(uiScreen->ScreenName.c_str());
		uiScreen->DrawUI();
		ImGui::End();
	}

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void ColdTable::GraphicsEngine::OnKeyDown(int key)
{
	if (key == EKeyCode::ESCAPE_KEY)
	{
		InputSystem::Instance->CloseGameCallback();
	}
}

ColdTable::VertexBufferPtr ColdTable::GraphicsEngine::CreateVertexBuffer()
{
	return _graphicsDevice->CreateVertexBuffer();
}

ColdTable::IndexBufferPtr ColdTable::GraphicsEngine::CreateIndexBuffer()
{
	return _graphicsDevice->CreateIndexBuffer();
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
	_graphicsDevice->_d3dContext->CSSetShader(computeShader->_computeShader, nullptr, 0);
	_graphicsDevice->_d3dContext->CSSetShaderResources(0, 1, &computeShader->resourceView);
	_graphicsDevice->_d3dContext->CSSetUnorderedAccessViews(0, 1, &computeShader->unorderedAccessView, nullptr);
}

ColdTable::MaterialPtr ColdTable::GraphicsEngine::CreateMaterial(ShaderPtr shader)
{
	return std::make_shared<ColdTable::Material>(MaterialDesc {shader, _deviceContext});
}
