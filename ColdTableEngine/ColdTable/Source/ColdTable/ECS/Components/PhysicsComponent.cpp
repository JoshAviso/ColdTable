#include "PhysicsComponent.h"
#include <vector>

#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Editor/ActionTracking/EditActions/EditFloatAction.h"
#include "ColdTable/Editor/ActionTracking/EditActions/EditRBTypeAction.h"
#include "ColdTable/Utility/JsonParser.h"
#include "DearImGUI/imgui.h"

ColdTable::PhysicsComponent::PhysicsComponent(GameObjectPtr Owner, float mass) : Component(Owner, { EComponentType::Rigidbody }), _mass(mass)
{
	PhysicsCommon* physicsCommon = PhysicsSystem::GetInstance()->_physicsCommon;
	PhysicsWorld* physicsWorld = PhysicsSystem::GetInstance()->_physicsWorld;

	_rigidBody = physicsWorld->createRigidBody(reactphysics3d::Transform{});

	Vec3 scale = Vec3::Identity;
	if (Owner != nullptr) Owner->transform->scale;
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.x / 2.0f, scale.y / 2.0f, scale.z / 2.0f));
	_collider = _rigidBody->addCollider(boxShape, reactphysics3d::Transform::identity());
}

ColdTable::PhysicsComponent::~PhysicsComponent()
{
	if (_rigidBody != nullptr)
	PhysicsSystem::GetInstance()->_physicsWorld->destroyRigidBody(_rigidBody);
}

void ColdTable::PhysicsComponent::FromJson(const JsonValue& json)
{

	ComponentType = static_cast<EComponentType>(json["ComponentType"].AsNumber());
	ComponentTypes.push_back(ComponentType);
	enabled = json["Enabled"].AsBool();

	_mass = json["Mass"].AsNumber();
	_bodyType = static_cast<BodyType>(json["BodyType"].AsNumber());

}

ColdTable::JsonValue ColdTable::PhysicsComponent::ToJson() const
{
	JsonValue json;
	json["ComponentType"] = JsonValue(static_cast<double>(ComponentType));
	json["Enabled"] = JsonValue(enabled);
	json["Mass"] = JsonValue(_mass);
	json["BodyType"] = JsonValue(static_cast<double>(_bodyType));

	return json;
}

ColdTable::ComponentPtr ColdTable::PhysicsComponent::Clone(GameObjectPtr newOwner) const
{
	std::shared_ptr<PhysicsComponent> component = std::make_shared<PhysicsComponent>(newOwner, _mass);
	component->_bodyType = _bodyType;
	return component;
}

void ColdTable::PhysicsComponent::DrawToUI()
{
	float oldMass = _mass; reactphysics3d::BodyType oldType = _bodyType;

	String previewText = "Null";
	switch (_bodyType)
	{
	case reactphysics3d::BodyType::STATIC:
		previewText = "Static";
		break;
	case reactphysics3d::BodyType::DYNAMIC:
		previewText = "Dynamic";
		break;
	case reactphysics3d::BodyType::KINEMATIC:
		previewText = "Kinematic";
		break;
	}

	ImGui::Checkbox("##RBEnable", &enabled); ImGui::SameLine();
	if (ImGui::TreeNode("Rigidbody"))
	{
		ImGui::Text("Mass: "); ImGui::SameLine();
		ImGui::InputFloat("##RBMass", &_mass);

		ImGui::Text("Type: "); ImGui::SameLine();
		if (ImGui::BeginCombo("##BodyType", previewText.c_str()))
		{
			if (ImGui::Selectable("Static", _bodyType == reactphysics3d::BodyType::STATIC))
			{
				_bodyType = reactphysics3d::BodyType::STATIC;
			}
			if (ImGui::Selectable("Dynamic", _bodyType == reactphysics3d::BodyType::DYNAMIC))
			{
				_bodyType = reactphysics3d::BodyType::DYNAMIC;
			}
			if (ImGui::Selectable("Kinematic", _bodyType == reactphysics3d::BodyType::KINEMATIC))
			{
				_bodyType = reactphysics3d::BodyType::KINEMATIC;
			}
			ImGui::EndCombo();
		}

		ImGui::TreePop();
	}

	if (ActionManager::Instance != nullptr)
	{
		if (oldMass != _mass) ActionManager::Instance->PushAction(std::make_unique<EditFloatAction>(&_mass, oldMass, _mass));
		if (oldType != _bodyType) ActionManager::Instance->PushAction(std::make_unique<EditRBTypeAction>(&_bodyType, oldType, _bodyType));
	}
}
