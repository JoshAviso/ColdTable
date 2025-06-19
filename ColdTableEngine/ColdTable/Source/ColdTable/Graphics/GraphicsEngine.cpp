#include <ColdTable/Graphics/GraphicsEngine.h>
#include <ColdTable/Graphics/GraphicsDevice.h>
#include <ColdTable/Graphics/DeviceContext.h>
#include <ColdTable/Graphics/VertexBuffer.h>
#include <d3dcompiler.h>
#include <iostream>

#include "Camera.h"
#include "ColdTable/Math/Vertex.h"
#include "ColdTable/Resource/Mesh/Mesh.h"
#include "ColdTable/Utility/Utils.h"
#include "DearImGUI/imgui.h"
#include "DearImGUI/imgui_impl_dx11.h"
#include "DearImGUI/imgui_impl_win32.h"

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

void ColdTable::GraphicsEngine::RegisterMesh(MeshPtr mesh)
{
	_meshes.push_back(mesh);
}

void ColdTable::GraphicsEngine::UnregisterMesh(MeshPtr mesh)
{
	std::vector<MeshPtr>::iterator index{};
	for (auto itr = _meshes.begin(); itr != _meshes.end(); ++itr)
	{
		if (*itr == mesh)
		{
			index = itr;
			break;
		}
	}

	if (index != _meshes.end())
		_meshes.erase(index);
}

void ColdTable::GraphicsEngine::RegisterLight(const DirectionalLightPtr& light)
{
	_directionalLights.push_back(light);
}

void ColdTable::GraphicsEngine::UnregisterLight(const DirectionalLightPtr& light)
{
	std::vector<DirectionalLightPtr>::iterator index{};
	for (auto itr = _directionalLights.begin(); itr != _directionalLights.end(); ++itr)
	{
		if (*itr == light)
		{
			index = itr;
			break;
		}
	}

	if (index != _directionalLights.end())
		_directionalLights.erase(index);
}

void ColdTable::GraphicsEngine::RegisterLight(const SpotLightPtr& light)
{
	_spotLights.push_back(light);
}

void ColdTable::GraphicsEngine::UnregisterLight(const SpotLightPtr& light)
{
}

void ColdTable::GraphicsEngine::RegisterLight(const PointLightPtr& light)
{
	_pointLights.push_back(light);
}

void ColdTable::GraphicsEngine::UnregisterLight(const PointLightPtr& light)
{
}

void ColdTable::GraphicsEngine::RegisterComputeShader(ComputeShaderPtr computeShader)
{
	_deviceContext->BindComputeShader(computeShader);
}

ColdTable::GraphicsDevicePtr ColdTable::GraphicsEngine::GetGraphicsDevice() noexcept
{
	return _graphicsDevice;
}

/*
void ColdTable::GraphicsEngine::UpdateConstantBuffer(const ConstantBufferPtr& constantBuffer, ConstantBufferContent content)
{
	constantBuffer->Update(&*_deviceContext, &content);
	_deviceContext->BindConstantBuffer(constantBuffer, 0);
}
*/

void ColdTable::GraphicsEngine::Render(CameraPtr camera, SwapChain& swapChain, ConstantBufferPtr lightBuffer, Rect viewportSize)
{
	screensize = viewportSize;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	//ImGui::ShowDemoWindow();

	ImDrawList* drawList = ImGui::GetWindowDrawList();
	ImU32 color = IM_COL32(255, 0, 0, 255);
	for (CircleObject& circle : _circles)
	{
		Vec2 normalizeCircleVec = circle.circleVec.normalize();
		Vec2 tempCirclePos = circle.circlePos + (normalizeCircleVec * circleSpeed);
		if (tempCirclePos.x + circleRad > viewportSize.width || tempCirclePos.x - circleRad < 0)
			circle.circleVec.x = -circle.circleVec.x;
		else if (tempCirclePos.y + circleRad > viewportSize.height || tempCirclePos.y - circleRad < 0)
			circle.circleVec.y = -circle.circleVec.y;

		circle.circlePos = tempCirclePos;
		ImVec2 circlepos{ circle.circlePos.x, circle.circlePos.y};
		drawList->AddCircleFilled(circlepos, circleRad, color);
	}

	ImGui::Render();

	auto& context = *_deviceContext;
	context.ClearAndSetBackBuffer(swapChain, {0.2, 0.2, 0.5, 1});
	context.SetViewportSize(viewportSize);

	for (auto dirLight : _directionalLights)
	{
		dirLight->Update();
	}

	_spotLights[0]->position = camera->localPosition;
	_spotLights[0]->direction = camera->localRotation.forward();

	LightConstantBufferContent lightBufferContent{
		{
		{_directionalLights[0]->data, _directionalLights[0]->direction},
		{_directionalLights[1]->data, _directionalLights[1]->direction}
		},
		{_pointLights[0]->data, _pointLights[0]->position},
		SpotLightContent{
			_spotLights[0]->data,
			_spotLights[0]->position,
			_spotLights[0]->direction,
			_spotLights[0]->innerCutoff,
			_spotLights[0]->outerCutoff
		},
	};
	lightBuffer->Update(&context, &lightBufferContent);
	_deviceContext->BindConstantBuffer(lightBuffer, 0);

	CameraBufferContent camBuffer{
		camera->viewMatrix(),
		camera->projectionMat,
		camera->localPosition
	};
	camera->_cameraBuffer->Update(&context, &camBuffer);
	_deviceContext->BindConstantBuffer(camera->_cameraBuffer, 1);

	// Draw Renderables
	for (auto renderable : _renderables)
	{
		renderable->Update(EngineTime::GetDeltaTime());

		PerObjectBufferContent objectBuffer{
			renderable->transformMat(),
			renderable->_material->tint
		};

		renderable->_material->SetData(&objectBuffer, sizeof(PerObjectBufferContent));
		_deviceContext->BindConstantBuffer(renderable->_material->_constantBuffer, 2);
		context.Draw(renderable);
	}

	// Draw Meshes
	for (auto mesh : _meshes)
	{
		PerObjectBufferContent objectBuffer{
			Mat4::Identity,
			mesh->_material->tint
		};

		mesh->_material->SetData(&objectBuffer, sizeof(PerObjectBufferContent));
		_deviceContext->BindConstantBuffer(mesh->_material->_constantBuffer, 2);
		context.Draw(mesh);
	}

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	auto& device = *_graphicsDevice;
	device.ExecuteCommandList(context);

	/*
	bool myToolActive;
	ImGui::Begin("Hello World", &myToolActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar()) {

		if (ImGui::BeginMenu("File")) {

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	ImGui::End();
	*/


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

void ColdTable::GraphicsEngine::OnKeyUp(int key)
{
	if (key == EKeyCode::SPACEBAR)
	{
		CircleObject circle{};
		circle.circlePos = Vec2(screensize.width / 2.0f, screensize.height / 2.0f);
		circle.circleVec.x = Utils::Random(-1.0f, 1.0f);
		circle.circleVec.y = Utils::Random(-1.0f, 1.0f);

		_circles.push_back(circle);
	}
	if (key == EKeyCode::BACKSPACE)
	{
		if (_circles.size() > 0)
			_circles.pop_back();
	}
	if (key == EKeyCode::DELETE_KEY)
	{
		_circles.clear();
	}
}

void ColdTable::GraphicsEngine::OnKeyDown(int key)
{
	if (key == EKeyCode::ESCAPE_KEY)
	{
		InputSystem::Instance->CloseGameCallback();
	}
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
	//_deviceContext->BindComputeShader(computeShader);
	_graphicsDevice->_d3dContext->CSSetShader(computeShader->_computeShader, nullptr, 0);

	_graphicsDevice->_d3dContext->CSSetShaderResources(0, 1, &computeShader->resourceView);
	_graphicsDevice->_d3dContext->CSSetUnorderedAccessViews(0, 1, &computeShader->unorderedAccessView, nullptr);
}

void ColdTable::GraphicsEngine::BindMaterial(MaterialPtr material)
{
	
}

ColdTable::MaterialPtr ColdTable::GraphicsEngine::CreateMaterial(ShaderPtr shader)
{
	MaterialDesc desc{
		shader, CreateConstantBuffer(), _deviceContext
	};
	return std::make_shared<Material>(desc);
}

void ColdTable::GraphicsEngine::UseShader(const ShaderPtr& shader)
{
	//_deviceContext->UseShader(shader);
}
