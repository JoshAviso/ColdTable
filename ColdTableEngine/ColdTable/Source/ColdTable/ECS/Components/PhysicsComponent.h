#pragma once
#include <vector>
#include <reactphysics3d/reactphysics3d.h>

#include "ColdTable/ECS/Components/Component.h"
#include "ColdTable/ECS/GameSystems/PhysicsSystem.h"
#include "ColdTable/Math/Vec3.h"
#include <ColdTable/Math/Quaternion.h>
#include <ColdTable/ECS/GameObjects/GameObject.h>

namespace ColdTable
{
	using namespace reactphysics3d;
	class PhysicsSystem;
	class PhysicsComponent : public Component
	{
	public:
		explicit PhysicsComponent(GameObjectPtr Owner, float mass);
		~PhysicsComponent();

		JsonValue ToJson() const override;
		void FromJson(const JsonValue& json) override;

		ComponentPtr Clone(GameObjectPtr newOwner) const override;
		void DrawToUI() override;

		float _mass;
		BodyType _bodyType = BodyType::DYNAMIC;
		RigidBody* _rigidBody;
		Collider* _collider;

		friend class PhysicsSystem;
	};
}

