#include "Component.h"

#include <unordered_set>

#include <ColdTable/Math/Mat4.h>

#include <ColdTable/ECS/GameObjects/GameObject.h>

ColdTable::Component::Component(GameObjectPtr Owner, const std::initializer_list<EComponentType> componentTypes) : Owner(Owner)
{
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
