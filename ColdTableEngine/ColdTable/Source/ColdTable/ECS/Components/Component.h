#pragma once
#include <vector>

#include "ColdTable/Core/Core.h"


namespace ColdTable
{
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
		Component(const std::initializer_list<EComponentType> componentTypes);
		Component(const EComponentType componentTypes[]);

	private:
		std::vector<EComponentType> ComponentTypes;

	protected:
		GameObjectPtr Owner;

		friend class ECSEngine;
		friend class GameObject;
	};
	using ComponentPtr = std::shared_ptr<Component>;
}

