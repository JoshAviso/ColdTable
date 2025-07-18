#pragma once
#include "GameSystem.h"
#include <reactphysics3d/reactphysics3d.h>

namespace ColdTable
{
	using namespace reactphysics3d;
	class PhysicsSystem : public GameSystem
	{
	public:
		PhysicsSystem();
		void Start(std::vector<ComponentPtr>& components) override;
		void Update(std::vector<ComponentPtr>& components) override;


		PhysicsCommon* _physicsCommon;
		PhysicsWorld* _physicsWorld;
		bool _isPaused = false;

		static PhysicsSystem* GetInstance();

	private:
		static PhysicsSystem* instance;
	};
}

