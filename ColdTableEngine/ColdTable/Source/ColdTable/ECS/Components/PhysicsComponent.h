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
	class PhysicsComponent : public Component
	{
	public:
		explicit PhysicsComponent(GameObjectPtr Owner, float mass) : Component(Owner, { EComponentType::Physics }), _mass(mass)
		{
			PhysicsCommon* physicsCommon = PhysicsSystem::GetInstance()->_physicsCommon;
			PhysicsWorld* physicsWorld = PhysicsSystem::GetInstance()->_physicsWorld;

			Vec3 scale = Owner->transform->scale;

			reactphysics3d::Transform transform;
			Quaternion localRot = Owner->transform->rotation.asRotationQuaternion();
			transform.setOrientation(reactphysics3d::Quaternion(localRot.x, localRot.y, localRot.z, localRot.w));
			transform.setPosition(Vector3(Owner->transform->position.x, Owner->transform->position.y, Owner->transform->position.z));

			BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2.0f, scale.y / 2.0f, scale.z / 2.0f));

			_rigidBody = physicsWorld->createRigidBody(transform);
			_rigidBody->addCollider(boxShape, reactphysics3d::Transform::identity());
			_rigidBody->updateMassFromColliders();
			_rigidBody->setMass(_mass);
			_rigidBody->setType(BodyType::DYNAMIC);

			transform = _rigidBody->getTransform();
			float matrix[16];

			transform.getOpenGLMatrix(matrix);

			Vector3 pos = transform.getPosition();
			//Owner->transform->setTransfrom(matrix);
			Owner->transform->position = Vec3(pos.x, pos.y, pos.z);
			Owner->transform->scale = scale;
		}

		float _mass;
		RigidBody* _rigidBody;


		friend class PhysicsSystem;
	};
}

