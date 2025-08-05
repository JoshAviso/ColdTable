#pragma once
#include "GameSystem.h"
#include <reactphysics3d/reactphysics3d.h>

#include "ColdTable/ECS/Components/PhysicsComponent.h"

namespace ColdTable
{
	using namespace reactphysics3d;
	class PhysicsComponent;
	class PhysicsSystem : public GameSystem
	{
	public:
		PhysicsSystem();
		void Start(std::vector<ComponentPtr>& components) override;
		void Update(std::vector<ComponentPtr>& components) override;

		PhysicsCommon* _physicsCommon;
		PhysicsWorld* _physicsWorld;

		static PhysicsSystem* GetInstance();

	private:
		static PhysicsSystem* instance;
		void UpdateBasedOnOwner(std::shared_ptr<PhysicsComponent> component);
		void UpdateOwner(std::shared_ptr<PhysicsComponent> component);
	};
}

