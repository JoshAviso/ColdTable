#include "SpawnStairsScreen.h"

#include "ColdTable/Core/Core.h"
#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Resource/ShaderLibrary.h"
#include "ColdTable/Graphics/Renderables/Stair.h"

void ColdTable::SpawnStairsScreen::DrawUI()
{
	ImGui::Text("Settings:");
	ImGui::SliderInt("Step Count", &_stepCount, 2, 100);
	ImGui::SliderFloat("Shape Width", &_width, 0.1f, 100.0f);
	ImGui::Checkbox("Edit Individual Steps", &_editingPerStepSettings);
	if (_editingPerStepSettings)
	{
		ImGui::SliderFloat("Step Height", &_stepHeight, 0.1f, 10.0f);
		ImGui::SliderFloat("Step Depth", &_stepDepth, 0.1f, 10.0f);
		UpdateShapeStats();
	} else
	{
		ImGui::SliderFloat("Shape Height", &_height, 0.1f, 100.0f);
		ImGui::SliderFloat("Shape Length", &_length , 0.1f, 100.0f);
		UpdateStepStats();
	}
	if (ImGui::Button("Spawn Stairs"))
	{
		SpawnStairs();
		ShowScreen = false;
	}
}

void ColdTable::SpawnStairsScreen::UpdateStepStats()
{
	_stepHeight = _height / (float)_stepCount;
	_stepDepth = _length / (float)_stepCount;
}

void ColdTable::SpawnStairsScreen::UpdateShapeStats()
{
	_height = _stepHeight * (float)_stepCount;
	_length = _stepDepth * (float)_stepCount;
}

void ColdTable::SpawnStairsScreen::SpawnStairs()
{
	GameObjectPtr stairs = GameObjectManager::CreateGameObject("Stairs");
	StairDesc stairDesc{
		_stepCount,
		_height,
		_width,
		_length,
	};
	stairs->renderable = std::make_shared<Stair>(stairDesc, GraphicsEngine::Instance->CreateIndexBuffer(), ShaderLibrary::GetShader("BlankShader"));
}
