#pragma once
#include <vector>

#include "ColdTable/ECS/Components/Component.h"
#include "ColdTable/ECS/Components/Transform.h"
#include "ColdTable/Editor/IEditorPickable.h"
#include <memory>

#include "ColdTable/ECS/ECSEngine.h"

namespace ColdTable {
class GameObject : public IEditorPickable, public std::enable_shared_from_this<GameObject>
{
public:
	String name;
	Transform* transform;
	RenderablePtr renderable;

public:
	GameObject(String name);
	static void Destroy(GameObject* gameObject);
	void Destroy();
	~GameObject();
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

private:
	std::vector<ComponentPtr> _components;

};
}

