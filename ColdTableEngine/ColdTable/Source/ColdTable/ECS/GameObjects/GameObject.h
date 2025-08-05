#pragma once
#include <vector>

#include "ColdTable/ECS/Components/Component.h"
#include "ColdTable/ECS/Components/Transform.h"
#include "ColdTable/Editor/IEditorPickable.h"
#include <memory>

#include "ColdTable/ECS/ECSEngine.h"
#include "ColdTable/Utility/ISerializeable.h"

namespace ColdTable {
class GameObject : public IEditorPickable, public ISerializeable, public std::enable_shared_from_this<GameObject>
{
public:
	String name;
	bool enabled = true;
	Transform* transform;
	RenderablePtr renderable;

private:
	std::vector<ComponentPtr> _components;

public:
	GameObject(String name);
	GameObject(const GameObject& other) = default;
	GameObjectPtr Clone(bool registerComponents);
	static void Destroy(GameObject* gameObject);
	void Destroy();
	~GameObject();

	void FromJson(const JsonValue& json) override;
	JsonValue ToJson() const override;

	void DrawToUI() override;
	void Translate(Vec3 translation) override;
	void Rotate(Vec3 axis, float degree) override;
	void Scale(Vec3 scale) override;

	template <typename TComponent, typename... Args>
	TComponent* AddComponent(Args&&... args){
		static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must inherit from Component");

		std::shared_ptr<TComponent> component = std::make_shared<TComponent>(shared_from_this(), std::forward<Args>(args)...);
		_components.push_back(component);
		ECSEngine::GetInstance()->RegisterComponent(component);
		return component.get();
	}

	template <typename TComponent>
	std::shared_ptr<TComponent> GetComponent()
	{
		static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must inherit from Component");
		for (const auto& component : _components)
		{
			if (auto specificComponent = std::dynamic_pointer_cast<TComponent>(component)){
				return specificComponent;
			}
		}
		return nullptr;
	}

	template <typename TComponent>
	std::vector<std::shared_ptr<TComponent>> GetComponents()
	{
		static_assert(std::is_base_of<Component, TComponent>::value, "TComponent must inherit from Component");
		std::vector<std::shared_ptr<TComponent>> componentList{};
		for (const auto& component : _components)
		{
			if (auto specificComponent = std::dynamic_pointer_cast<TComponent>(component)) {
				componentList.push_back(specificComponent);
			}
		}

		return componentList;
	}

	void RemoveComponent(Component* component)
	{
		auto it = std::find_if(_components.begin(), _components.end(),
			[component](const std::shared_ptr<Component>& ptr) {
				return ptr.get() == component;
			});
		if (it != _components.end()) {
			ECSEngine::GetInstance()->UnregisterComponent(*it);
			_components.erase(it);
		}
	}

};
}

