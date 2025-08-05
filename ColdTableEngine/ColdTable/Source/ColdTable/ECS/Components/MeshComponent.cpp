#include <ColdTable/ECS/Components/MeshComponent.h>

#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Editor/ActionTracking/EditActions/EditMeshAction.h"
#include "ColdTable/Resource/Material/MaterialLibrary.h"
#include "ColdTable/Resource/Mesh/MeshManager.h"
#include "ColdTable/Utility/JsonParser.h"
#include "DearImGUI/imgui.h"

ColdTable::MeshComponent::MeshComponent(GameObjectPtr Owner) :
	Component(Owner, {EComponentType::MeshComponentType }){}

ColdTable::MeshComponent::MeshComponent(GameObjectPtr Owner, MeshPtr mesh) :
	Component(Owner, { EComponentType::MeshComponentType }), Mesh(mesh)
{
}

void ColdTable::MeshComponent::FromJson(const JsonValue& json)
{
	ComponentType = static_cast<EComponentType>(json["ComponentType"].AsNumber());
	ComponentTypes.push_back(ComponentType);
	enabled = json["Enabled"].AsBool();
	Mesh = MeshManager::Instance->GetMesh(json["MeshID"].AsString());

}

ColdTable::JsonValue ColdTable::MeshComponent::ToJson() const
{
	JsonValue json;
	json["ComponentType"] = JsonValue(static_cast<double>(ComponentType));
	json["Enabled"] = JsonValue(enabled);
	json["MeshID"] = JsonValue(MeshManager::Instance->FindMeshKey(Mesh));

	return json;
}

ColdTable::ComponentPtr ColdTable::MeshComponent::Clone(GameObjectPtr newOwner) const
{
	return std::make_shared<MeshComponent>(newOwner, Mesh);
}

void ColdTable::MeshComponent::DrawToUI()
{
	MeshPtr oldMesh = Mesh;
	String preview = "None";
	std::unordered_map<String, MeshPtr> map = MeshManager::Instance->_meshLibrary;
	if (Mesh != nullptr)
	{
		auto it = std::find_if(map.begin(), map.end(),
			[&](const auto& pair) { return pair.second == Mesh; });

		if (it != map.end()) preview = it->first;
	}

	ImGui::Checkbox("##MeshEnable", &enabled); ImGui::SameLine();
	if (ImGui::TreeNode("Mesh Component"))
	{
		ImGui::Text("Mesh:");
		ImGui::SameLine(); ImGui::PushItemWidth(150.f);
		if (ImGui::BeginCombo("##MeshSelect", preview.c_str()))
		{
			if (ImGui::Selectable("None", Mesh == nullptr))
			{
				Mesh = nullptr;
			}
			for (const auto& pair : map)
			{
				if (ImGui::Selectable(pair.first.c_str(), pair.second == Mesh))
				{
					Mesh = pair.second;
				}
			}

			ImGui::EndCombo();
		}

		ImGui::PopItemWidth();
		ImGui::TreePop();
	}
	if (ActionManager::Instance != nullptr)
	{
		if (oldMesh != Mesh) ActionManager::Instance->PushAction(std::make_unique<EditMeshAction>(&(Mesh), oldMesh, Mesh));
	}
}
