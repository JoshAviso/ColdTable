#include "HierarchyScreen.h"

#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "DearImGUI/imgui.h"

ColdTable::HierarchyScreen::HierarchyScreen() : IUIScreen("Hierarchy")
{

}


void ColdTable::HierarchyScreen::DrawUI()
{
	if (GameObjectManager::Instance == nullptr) return;

	
    ImGuiStyle& style = ImGui::GetStyle();
	float width = ImGui::GetContentRegionAvail().x;
	for (auto gameObject : GameObjectManager::Instance->_registeredObjects)
	{
	    float height = ImGui::CalcTextSize(gameObject->name.c_str()).y + style.FramePadding.y * 2.0f;
		if (ImGui::Button(gameObject->name.c_str(), ImVec2(width, height)))
		{
			EditorUIManager::Instance->InspectorSelected = gameObject;
			Logger::Log(Logger::LogLevel::Info, ("Selected GameObject: " + gameObject->name).c_str());
		}
	}
}
