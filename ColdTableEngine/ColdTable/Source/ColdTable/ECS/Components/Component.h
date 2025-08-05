#pragma once
#include <vector>

#include "ColdTable/Core/Core.h"
#include "ColdTable/Editor/IInspectorViewable.h"

namespace ColdTable
{
	class GameObject;
	enum EComponentType
	{
		None,
		Debug,
		Renderer,
		Rigidbody,
		MaterialComponentType,
		MeshComponentType,
		Light,
	};
	class Component;
	using ComponentPtr = std::shared_ptr<Component>;
	class Component : public IInspectorViewable, public ISerializeable
	{
	public:
		Component(GameObjectPtr Owner, const std::initializer_list<EComponentType> componentTypes);
		Component(GameObjectPtr Owner, const EComponentType componentTypes[]);
		virtual ~Component() = default;
		static void Destroy(std::shared_ptr<Component> component);

		static ComponentPtr MakeFromJson(const JsonValue& json);
		virtual JsonValue ToJson() const override = 0;

		virtual std::shared_ptr<Component> Clone(GameObjectPtr newOwner) const { return nullptr; }

		void DrawToUI() override;

		bool enabled = true;

	protected:
		std::vector<EComponentType> ComponentTypes;
		EComponentType ComponentType;
		GameObjectPtr Owner;

		friend class ECSEngine;
		friend class GameObject;
	};
}

