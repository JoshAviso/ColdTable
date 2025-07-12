#pragma once
#include "ColdTable/ECS/Components/Transform.h"
#include "ColdTable/Editor/IEditorPickable.h"

namespace ColdTable {
using String = std::string;

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

};
}

