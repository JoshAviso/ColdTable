#include "PhysicsSystem.h"

#include "ColdTable/ECS/Components/MeshComponent.h"
#include "ColdTable/ECS/Components/PhysicsComponent.h"
#include "ColdTable/Game/EngineTime.h"
#include "ColdTable/Resource/Mesh/Mesh.h"

using namespace reactphysics3d;
ColdTable::PhysicsSystem* ColdTable::PhysicsSystem::instance = nullptr;
ColdTable::PhysicsSystem::PhysicsSystem() : GameSystem({ EComponentType::Rigidbody })
{
	if (instance != nullptr) return;

	instance = this;
	_physicsCommon = new PhysicsCommon();
	PhysicsWorld::WorldSettings settings;
	settings.defaultVelocitySolverNbIterations = 50;
	settings.gravity = Vector3(0, -9.81, 0);
	this->_physicsWorld = _physicsCommon->createPhysicsWorld(settings);
}

void ColdTable::PhysicsSystem::Start(std::vector<ComponentPtr>& components)
{

}

void ColdTable::PhysicsSystem::Update(std::vector<ComponentPtr>& components)
{
	// Copy Current data to reflect changes
	for (auto component : components)
		UpdateBasedOnOwner(std::static_pointer_cast<PhysicsComponent>(component));

	// Update Physics World
	float deltaTime = EngineTime::GetDeltaTime();
	if (deltaTime > 0.0f) _physicsWorld->update(deltaTime);

	// Update Owners to reflect physics changes
	for (auto component : components)
		UpdateOwner(std::static_pointer_cast<PhysicsComponent>(component));
}

ColdTable::PhysicsSystem* ColdTable::PhysicsSystem::GetInstance()
{
	return instance;
}

void ColdTable::PhysicsSystem::UpdateBasedOnOwner(std::shared_ptr<PhysicsComponent> component)
{
	component->_rigidBody->setTransform(
		reactphysics3d::Transform(
			reactphysics3d::Vector3(component->Owner->transform->position.x, component->Owner->transform->position.y, component->Owner->transform->position.z),
			reactphysics3d::Quaternion(component->Owner->transform->rot.x, component->Owner->transform->rot.y, component->Owner->transform->rot.z, component->Owner->transform->rot.w)
		)
	);

	if (component->_collider != nullptr)
	{
		component->_rigidBody->removeCollider(component->_collider);
		component->_collider = nullptr;

		if (component->enabled)
		{
			Vec3 extent = component->Owner->transform->scale;
			MeshComponentPtr meshComponent = component->Owner->GetComponent<MeshComponent>();
			if (meshComponent != nullptr)
			{
				MeshPtr mesh = meshComponent->Mesh;
				if (mesh != nullptr)
				{
					Vec3 aabbMin{}; Vec3 aabbMax{};
					if (mesh->GetAABB(aabbMin, aabbMax))
					{
						extent.x = aabbMax.x - aabbMin.x;
						extent.y = aabbMax.y - aabbMin.y;
						extent.z = aabbMax.z - aabbMin.z;
						extent *= component->Owner->transform->scale;
					}
				}
			}

			BoxShape* boxShape = _physicsCommon->createBoxShape(Vector3(extent.x / 2.0f, extent.y / 2.0f, extent.z / 2.0f));
			component->_collider = component->_rigidBody->addCollider(boxShape, reactphysics3d::Transform::identity());
		}
	}

	component->_rigidBody->updateMassFromColliders();
	component->_rigidBody->setMass(component->_mass);
	component->_rigidBody->setType(component->_bodyType);
}

void ColdTable::PhysicsSystem::UpdateOwner(std::shared_ptr<PhysicsComponent> component)
{
	if (!component->enabled) return;
	reactphysics3d::Transform transform = component->_rigidBody->getTransform();

	Vector3 pos = transform.getPosition();
	component->Owner->transform->position = Vec3(pos.x, pos.y, pos.z);

	reactphysics3d::Quaternion quat = transform.getOrientation();
	Quaternion rotationQuat({ quat.x, quat.y, quat.z, quat.w });
	component->Owner->transform->rot = rotationQuat;
}
