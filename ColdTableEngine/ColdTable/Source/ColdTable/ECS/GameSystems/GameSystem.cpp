#include "GameSystem.h"

#include <unordered_set>

ColdTable::GameSystem::GameSystem(const std::initializer_list<ColdTable::EComponentType> targetComponentTypes)
{
	std::unordered_set<EComponentType> seen(TargetComponentTypes.begin(), TargetComponentTypes.end());
	for (EComponentType componentType : targetComponentTypes)
	{
		if (seen.insert(componentType).second)
		{
			TargetComponentTypes.push_back(componentType);
		}
	}
}

ColdTable::GameSystem::GameSystem(const ColdTable::EComponentType targetComponentTypes[])
{
	// std::unordered_set<EComponentType> seen(TargetComponentTypes.begin(), TargetComponentTypes.end());
	// for (EComponentType componentType : targetComponentTypes)
	// {
	// 	if (seen.insert(componentType).second)
	// 	{
	// 		TargetComponentTypes.push_back(componentType);
	// 	}
	// }
}
