#pragma once
#include <vector>

#include "ColdTable/ECS/Components/Component.h"
#include "ColdTable/ECS/Components/Transform.h"
#include "ColdTable/Editor/IEditorPickable.h"

namespace ColdTable {
class GameObject : public IEditorPickable
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

	void AddComponent(ComponentPtr component);

private:
	std::vector<ComponentPtr> _components;

};
}

