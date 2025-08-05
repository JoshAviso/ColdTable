#include <ColdTable/ECS/Components/LightComponent.h>

#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Resource/Mesh/MeshManager.h"
#include "DearImGUI/imgui.h"

/*
ColdTable::LightComponent::LightComponent(GameObjectPtr Owner) :
	Component(Owner, {EComponentType::Light}){}

ColdTable::MeshComponent::MeshComponent(GameObjectPtr Owner, MeshPtr mesh) :
	Component(Owner, { EComponentType::Graphics }), Mesh(mesh)
{
}

ColdTable::ComponentPtr ColdTable::MeshComponent::Clone(GameObjectPtr newOwner) const
{
	return std::make_shared<MeshComponent>(newOwner, Mesh);
}

void ColdTable::MeshComponent::DrawToUI()
{
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
}
*/