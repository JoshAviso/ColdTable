#include <ColdTable/Editor/UIScreens/SelectorTypeScreen.h>

#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Graphics/GraphicsEngine.h"
#include "DearImGUI/imgui.h"

ColdTable::SelectorTypeScreen::SelectorTypeScreen(): IUIScreen("Selector")
{
}

void ColdTable::SelectorTypeScreen::DrawUI()
{
	if (GraphicsEngine::Instance == nullptr) return;

	if (GameObjectManager::Instance != nullptr)
	{
		ImGui::InputFloat("Grid Snapping", &GameObjectManager::Instance->gridSnapping, 0.05f, 0.5f);
		ImGui::InputFloat("Rot Snapping", &GameObjectManager::Instance->rotSnapping, 5, 15);
		ImGui::InputFloat("Scale Snapping", &GameObjectManager::Instance->scaleSnapping, 0.05f, 0.5f);

	}

	ImGui::Text("Select Mode:");
	switch (GraphicsEngine::Instance->_pickupMode)
	{
	case EPickableType::PickupObject:
		ImGui::Text("Current: (Object)");
		break;
	case PickupVertex:
		ImGui::Text("Current: (Vertex)");
		break;
	case PickupFace:
		ImGui::Text("Current: (Face)");
		break;
	case PickupEdge:
		ImGui::Text("Current: (Edge)");
		break;
	}
	if (ImGui::Button("Object Picking"))
	{
		GraphicsEngine::Instance->_pickupMode = EPickableType::PickupObject;
	}
	if (ImGui::Button("Face Picking"))
	{
		GraphicsEngine::Instance->_pickupMode = EPickableType::PickupFace;
	}
	if (ImGui::Button("Edge Picking"))
	{
		GraphicsEngine::Instance->_pickupMode = EPickableType::PickupEdge;
	}
	if (ImGui::Button("Vertex Picking"))
	{
		GraphicsEngine::Instance->_pickupMode = EPickableType::PickupVertex;
	}
}
