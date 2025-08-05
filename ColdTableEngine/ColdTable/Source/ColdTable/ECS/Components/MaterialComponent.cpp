#include "MaterialComponent.h"

#include <unordered_map>

#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Editor/ActionTracking/EditActions/EditMatAction.h"
#include "ColdTable/Resource/Material/MaterialLibrary.h"
#include "ColdTable/Utility/JsonParser.h"
#include "DearImGUI/imgui.h"

ColdTable::MaterialComponent::MaterialComponent(GameObjectPtr Owner) :
	MaterialComponent(Owner, MaterialLibrary::GetMaterial("Default")){}

ColdTable::MaterialComponent::MaterialComponent(GameObjectPtr Owner, MaterialPtr Material) :
	Component(Owner, {EComponentType::MaterialComponentType}),
	_material(Material)
{

}

void ColdTable::MaterialComponent::FromJson(const JsonValue& json)
{
	ComponentType = static_cast<EComponentType>(json["ComponentType"].AsNumber());
	ComponentTypes.push_back(ComponentType);
	enabled = json["Enabled"].AsBool();
	_material = MaterialLibrary::GetMaterial(json["MaterialID"].AsString());
}

ColdTable::JsonValue ColdTable::MaterialComponent::ToJson() const
{
	JsonValue json;
	json["ComponentType"] = JsonValue(static_cast<double>(ComponentType));
	json["Enabled"] = JsonValue(enabled);
	json["MaterialID"] = JsonValue(MaterialLibrary::GetMaterialKey(_material));

	return json;
}

ColdTable::ComponentPtr ColdTable::MaterialComponent::Clone(GameObjectPtr newOwner) const
{
	return std::make_shared<MaterialComponent>(newOwner, _material);
}

void ColdTable::MaterialComponent::DrawToUI()
{
	MaterialPtr oldMat = _material;
	String preview = "None";
	std::unordered_map<String, MaterialPtr> map = MaterialLibrary::Instance->_managedMaterials;
	if (_material != nullptr)
	{
		auto it = std::find_if(map.begin(), map.end(),
			[&](const auto& pair) { return pair.second == _material; });

		if (it != map.end()) preview = it->first;
	}

	ImGui::Checkbox("##MaterialEnable", &enabled); ImGui::SameLine();
	if (ImGui::TreeNode("Material Component"))
	{
		ImGui::Text("Material:");
		ImGui::SameLine(); ImGui::PushItemWidth(125.f);
		if (ImGui::BeginCombo("##MatSelect", preview.c_str()))
		{
			for (const auto& pair : map)
			{
				if (ImGui::Selectable(pair.first.c_str(), pair.second == _material))
				{
					_material = pair.second;
				}
			}
			ImGui::EndCombo();
		}

		ImGui::PopItemWidth();
		ImGui::TreePop();
	}

	if (ActionManager::Instance != nullptr)
	{
		if (oldMat != _material) ActionManager::Instance->PushAction(std::make_unique<EditMatAction>(&(_material), oldMat, _material));
	}
}
