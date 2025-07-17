#pragma once
#include "GameSystem.h"
#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/Components/DebugBlurbComponent.h"
#include "ColdTable/ECS/GameObjects/GameObject.h"

namespace ColdTable
{
		class DebugBlurbSystem : public GameSystem
		{
		public:
			DebugBlurbSystem() : GameSystem({ EComponentType::Debug }) {}
			void Start(std::vector<ComponentPtr>& components) override
			{
				for (auto component : components)
				{
					std::shared_ptr<DebugBlurbComponent> blurb = std::static_pointer_cast<DebugBlurbComponent>(component);
					Logger::Log("Start: " + blurb->_blurbText + "(" + blurb->Owner->name + ")");
				}
			}
			void EarlyUpdate(std::vector<ComponentPtr>& components) override
			{
				for (auto component : components)
				{
					std::shared_ptr<DebugBlurbComponent> blurb = std::static_pointer_cast<DebugBlurbComponent>(component);
					Logger::Log("EarlyUpdate: " + blurb->_blurbText + "(" + blurb->Owner->name + ")");
				}
			}
			void Update(std::vector<ComponentPtr>& components) override
			{
				for (auto component : components)
				{
					std::shared_ptr<DebugBlurbComponent> blurb = std::static_pointer_cast<DebugBlurbComponent>(component);
					Logger::Log("Update: " + blurb->_blurbText + "(" + blurb->Owner->name + ")");
				}
			}
			void LateUpdate(std::vector<ComponentPtr>& components) override
			{
				for (auto component : components)
				{
					std::shared_ptr<DebugBlurbComponent> blurb = std::static_pointer_cast<DebugBlurbComponent>(component);
					Logger::Log("LateUpdate: " + blurb->_blurbText + "(" + blurb->Owner->name + ")");
				}
			}
		};
	
}

