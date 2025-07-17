#pragma once
#include <memory>
#include <vector>

#include "ColdTable/ECS/Components/Component.h"

namespace ColdTable
{
		class GameSystem
		{
		public:
			GameSystem(const std::initializer_list<EComponentType> targetComponentTypes);
			GameSystem(const EComponentType targetComponentTypes[]);
			virtual ~GameSystem() = default;
			virtual void Start			(std::vector<ComponentPtr>& components){}
			virtual void EarlyUpdate	(std::vector<ComponentPtr>& components){}
			virtual void Update			(std::vector<ComponentPtr>& components){}
			virtual void LateUpdate		(std::vector<ComponentPtr>& components){}
			virtual void FixedUpdate	(std::vector<ComponentPtr>& components){}
			virtual void Render			(std::vector<ComponentPtr>& components){}

		private:
			std::vector<EComponentType> TargetComponentTypes;

			friend class ECSEngine;
		};
		using GameSystemPtr = std::shared_ptr<GameSystem>;
		
	
}

