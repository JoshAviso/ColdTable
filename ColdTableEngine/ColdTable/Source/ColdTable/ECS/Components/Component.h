#pragma once
#include <vector>

#include "ColdTable/Core/Core.h"

namespace ColdTable
{
	class GameObject;
	enum EComponentType
	{
		None,
		Debug,
		Renderer,
		Physics,
	};
	class Component
	{
	public:
		Component(GameObjectPtr Owner, const std::initializer_list<EComponentType> componentTypes);
		Component(GameObjectPtr Owner, const EComponentType componentTypes[]);

	private:
		std::vector<EComponentType> ComponentTypes;

	protected:
		GameObjectPtr Owner;

		friend class ECSEngine;
		friend class GameObject;
	};
	using ComponentPtr = std::shared_ptr<Component>;
}

