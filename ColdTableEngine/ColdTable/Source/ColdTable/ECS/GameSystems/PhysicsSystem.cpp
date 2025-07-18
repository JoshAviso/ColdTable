#include "PhysicsSystem.h"

#include "ColdTable/ECS/Components/PhysicsComponent.h"
#include "ColdTable/Game/EngineTime.h"

using namespace reactphysics3d;
ColdTable::PhysicsSystem* ColdTable::PhysicsSystem::instance = nullptr;
ColdTable::PhysicsSystem::PhysicsSystem() : GameSystem({ EComponentType::Physics })
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
	if (_isPaused) return;
	float deltaTime = EngineTime::GetDeltaTime();
	if (deltaTime > 0.0f) _physicsWorld->update(deltaTime);
	for (auto component : components)
	{
		std::shared_ptr<PhysicsComponent> physicsComponent = std::static_pointer_cast<PhysicsComponent>(component);
		reactphysics3d::Transform transform = physicsComponent->_rigidBody->getTransform();

		Vec3 origScale = physicsComponent->Owner->transform->scale;
		float matrix[16];
		transform.getOpenGLMatrix(matrix);
		Vector3 pos = transform.getPosition();
		//Owner->transform->setTransfrom(matrix);
		physicsComponent->Owner->transform->position = Vec3(pos.x, pos.y, pos.z);

		reactphysics3d::Quaternion quat = transform.getOrientation();
		Quaternion rotationQuat({ quat.x, quat.y, quat.z, quat.w });
		physicsComponent->Owner->transform->rot = rotationQuat;

		physicsComponent->Owner->transform->scale = origScale;
		Logger::Log(physicsComponent->Owner->name + ": P:" + physicsComponent->Owner->transform->position.toString() + " S:" + physicsComponent->Owner->transform->scale.toString() + " R:" + physicsComponent->Owner->transform->rot.toString());
	}
}

ColdTable::PhysicsSystem* ColdTable::PhysicsSystem::GetInstance()
{
	return instance;
}
