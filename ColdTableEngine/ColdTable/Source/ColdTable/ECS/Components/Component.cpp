#include "Component.h"

#include <unordered_set>

#include <ColdTable/Math/Mat4.h>

#include <ColdTable/ECS/GameObjects/GameObject.h>

#include "MaterialComponent.h"
#include "MeshComponent.h"
#include "PhysicsComponent.h"
#include "ColdTable/Utility/JsonParser.h"
#include "DearImGUI/imgui.h"

ColdTable::Component::Component(GameObjectPtr Owner, const std::initializer_list<EComponentType> componentTypes) : Owner(Owner)
{
	auto it = componentTypes.begin();
	if (it != componentTypes.end()) {
		ComponentType = *it; 
	}

	std::unordered_set<EComponentType> seen(ComponentTypes.begin(), ComponentTypes.end());
	for (EComponentType componentType : componentTypes)
	{
		if (seen.insert(componentType).second)
		{
			ComponentTypes.push_back(componentType);
		}
	}
}

ColdTable::Component::Component(GameObjectPtr Owner, const EComponentType componentTypes[]) : Owner(Owner)
{
	// std::unordered_set<EComponentType> seen(ComponentTypes.begin(), ComponentTypes.end());
	// for (EComponentType componentType : componentTypes)
	// {
	// 	if (seen.insert(componentType).second)
	// 	{
	// 		ComponentTypes.push_back(componentType);
	// 	}
	// }
}

void ColdTable::Component::Destroy(ComponentPtr component)
{
	if (component->Owner != nullptr)
	{
		ECSEngine::GetInstance()->UnregisterComponent(component);
		component->Owner = nullptr;
	}
}

ColdTable::ComponentPtr ColdTable::Component::MakeFromJson(const JsonValue& json)
{
	EComponentType type = static_cast<EComponentType>(json["ComponentType"].AsNumber());
	switch (type)
	{
	case EComponentType::None:
		return nullptr; // No component to create
	case Rigidbody:{
		std::shared_ptr<PhysicsComponent> rb = std::make_shared<PhysicsComponent>(nullptr, 0.0f);
		rb->FromJson(json);
		return rb;
	}
	case MaterialComponentType:{
		MaterialComponentPtr mat = std::make_shared<MaterialComponent>(nullptr);
		mat->FromJson(json);
		return mat;
	}
	case MeshComponentType:{
		MeshComponentPtr mesh = std::make_shared<MeshComponent>(nullptr);
		mesh->FromJson(json);
		return mesh;
	}
	case Light:
		break;
	}
	return nullptr;
}

void ColdTable::Component::DrawToUI()
{
	ImGui::Text("+ %s", typeid(*this).name());
}
