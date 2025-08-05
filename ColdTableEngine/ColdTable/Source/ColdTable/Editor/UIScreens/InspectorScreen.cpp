#include "InspectorScreen.h"

#include "ColdTable/ECS/Components/MaterialComponent.h"
#include "ColdTable/ECS/Components/MeshComponent.h"
#include "ColdTable/ECS/Components/PhysicsComponent.h"
#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "DearImGUI/imgui.h"

ColdTable::InspectorScreen::InspectorScreen() : IUIScreen("Inspector")
{

}

void ColdTable::InspectorScreen::DrawUI()
{
	if (EditorUIManager::Instance->InspectorSelected == nullptr) return;

	GameObject* selected = EditorUIManager::Instance->InspectorSelected;
	selected->DrawToUI();

	if (ImGui::Button("Add Component"))
	{
		ImGui::OpenPopup("AddComponentPopup");
	}
	if (ImGui::BeginPopup("AddComponentPopup"))
	{
		if (ImGui::MenuItem("Add Mesh"))
		{
			selected->AddComponent<MeshComponent>();
		}
		if (ImGui::MenuItem("Add Material"))
		{
			selected->AddComponent<MaterialComponent>();
		}
		if (ImGui::MenuItem("Add Rigidbody"))
		{
			selected->AddComponent<PhysicsComponent>(1.0f);
		}
		ImGui::EndPopup();
	}
}
