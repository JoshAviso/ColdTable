#include "Component.h"

#include <unordered_set>

ColdTable::Component::Component(const std::initializer_list<EComponentType> componentTypes)
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

ColdTable::Component::Component(const EComponentType componentTypes[])
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
