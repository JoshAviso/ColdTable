#include "HierarchyScreen.h"

#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "DearImGUI/imgui.h"
#include "DearImGUI/imgui_internal.h"

ColdTable::HierarchyScreen::HierarchyScreen() : IUIScreen("Hierarchy")
{

}


void ColdTable::HierarchyScreen::DrawUI()
{
	if (GameObjectManager::Instance == nullptr) return;

    float width = ImGui::GetContentRegionAvail().x;

	float width2 = ImGui::GetContentRegionAvail().x;
	for (auto gameObject : GameObjectManager::Instance->_registeredObjects)
	{
        if (gameObject->transform->parent == nullptr)
			DrawGameObject(gameObject.get(), width2);
	}

    // Get window content region in screen coordinates
    ImVec2 contentMin = ImGui::GetWindowContentRegionMin();
    ImVec2 contentMax = ImGui::GetWindowContentRegionMax();
    ImVec2 windowPos = ImGui::GetWindowPos();
    ImVec2 rectMin = ImVec2(windowPos.x + contentMin.x, windowPos.y + contentMin.y);
    ImVec2 rectMax = ImVec2(windowPos.x + contentMax.x, windowPos.y + contentMax.y);
    ImVec2 size = ImVec2(rectMax.x - rectMin.x, rectMax.y - rectMin.y);

    // Set cursor to the top-left of the window content region
    ImGui::SetCursorScreenPos(rectMin);

    // Invisible button covering content area, allow item overlap so it doesn't block
    ImGui::InvisibleButton("##full_window_drop_target", size, ImGuiButtonFlags_AllowOverlap);

    // Drag target: accept dropping onto this node
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_GAMEOBJECT"))
        {
            IM_ASSERT(payload->DataSize == sizeof(GameObject*));
            GameObject* droppedGameObject = *(GameObject**)payload->Data;

            droppedGameObject->transform->RemoveParent();
        }
        ImGui::EndDragDropTarget();
    }
}

void ColdTable::HierarchyScreen::DrawGameObject(GameObject* gameObject, float width)
{
    if (gameObject == nullptr) return;

    ImGuiStyle& style = ImGui::GetStyle();

    bool hasChildren = !gameObject->transform->children.empty();
    bool isSelected = (EditorUIManager::Instance->InspectorSelected == gameObject);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth | (hasChildren ? 0 : ImGuiTreeNodeFlags_Leaf);
    if (isSelected)
        flags |= ImGuiTreeNodeFlags_Selected;

    bool isOpened = ImGui::TreeNodeEx(gameObject->name.c_str(), flags);

    if (ImGui::IsItemClicked())
        EditorUIManager::Instance->InspectorSelected = gameObject;

    // Drag source: start dragging this node
    if (ImGui::BeginDragDropSource())
    {
        ImGui::SetDragDropPayload("DND_GAMEOBJECT", &gameObject, sizeof(GameObject*));
        ImGui::TextUnformatted(gameObject->name.c_str());
        ImGui::EndDragDropSource();
    }

    // Drag target: accept dropping onto this node
    if (ImGui::BeginDragDropTarget())
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DND_GAMEOBJECT"))
        {
            IM_ASSERT(payload->DataSize == sizeof(GameObject*));
            GameObject* droppedGameObject = *(GameObject**)payload->Data;

            if (droppedGameObject && droppedGameObject != gameObject)
            {
                // Reparent droppedGameObject to this gameObject
                droppedGameObject->transform->AddParent(gameObject);
            }
        }
        ImGui::EndDragDropTarget();
    }

    if (isOpened)
    {
        if (hasChildren)
        {
            for (auto child : gameObject->transform->children)
            {
                if (child == nullptr) continue;
                if (child->gameObject != nullptr)
                    DrawGameObject(child->gameObject, width);
            }
        }
        ImGui::TreePop();
    }
}
