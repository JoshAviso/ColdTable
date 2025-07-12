#include "InspectorScreen.h"

#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "DearImGUI/imgui.h"

ColdTable::InspectorScreen::InspectorScreen() : IUIScreen("Inspector")
{

}

void ColdTable::InspectorScreen::DrawUI()
{
	if (EditorUIManager::Instance->InspectorSelected == nullptr) return;

	GameObjectPtr gameObject = EditorUIManager::Instance->InspectorSelected;
	ImGui::Text(gameObject->name.c_str());
}
