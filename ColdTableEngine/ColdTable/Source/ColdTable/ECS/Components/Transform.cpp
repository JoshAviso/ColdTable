#include "Transform.h"

#include "ColdTable/Math/Quaternion.h"
#include <ColdTable/Math/Mat4.h> 

#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Editor/ActionTracking/EditActions/EditQuatAction.h"
#include "ColdTable/Editor/ActionTracking/EditActions/EditVec3Action.h"
#include "ColdTable/Utility/JsonParser.h"
#include "DearImGUI/imgui.h"

void ColdTable::Transform::AddParent(Transform* transform)
{
	ProcessReparenting(transform, this, false);
}

void ColdTable::Transform::RemoveParent()
{
	if (parent == nullptr) return;
	ProcessReparenting(parent, this, true);
}

void ColdTable::Transform::AddChild(Transform* child)
{
	ProcessReparenting(this, child, false);
}

void ColdTable::Transform::RemoveChild(Transform* child)
{
	ProcessReparenting(this, child, true);
}

void ColdTable::Transform::AddParent(GameObject* parent)
{
	if (parent == nullptr) return;
	if (parent->transform == nullptr) return;
	AddParent(parent->transform);
}

void ColdTable::Transform::AddChild(GameObject* child)
{
	if (child == nullptr) return;
	if (child->transform == nullptr) return;
	AddChild(child->transform);
}

void ColdTable::Transform::RemoveChild(GameObject* child)
{
	if (child == nullptr) return;
	if (child->transform == nullptr) return;
	RemoveChild(child->transform);
}

void ColdTable::Transform::FromJson(const JsonValue& json)
{
	position = Vec3::FromJson(json["Position"]);
	scale = Vec3::FromJson(json["Scale"]);
	rot = Quaternion::FromJson(json["Rotation"]);
}

ColdTable::JsonValue ColdTable::Transform::ToJson() const
{
	JsonValue json;
	json["Position"] = Vec3::ToJson(position);
	json["Scale"] = Vec3::ToJson(scale);
	json["Rotation"] = Quaternion::ToJson(rot);
	return json;
}

ColdTable::Mat4 ColdTable::Transform::transformMat() const
{
	Mat4 parentMat = Mat4::Identity;
	if (parent != nullptr)
	{
		parentMat = parent->transformMat();
	};

	return
		parentMat *
		position.asTranslationMatrix() *
		rot.asMat() *
		scale.asScaleMatrix() 
	;
}

void ColdTable::Transform::setTransfrom(float (&matrix)[16])
{
	position = Vec3(matrix[12], matrix[13], matrix[14]);

	float Sx = Vec3(matrix[0], matrix[1], matrix[2]).magnitude();
	float Sy = Vec3(matrix[4], matrix[5], matrix[6]).magnitude();
	float Sz = Vec3(matrix[8], matrix[9], matrix[10]).magnitude();
	scale = Vec3(Sx, Sy, Sz);

	Vec3 R0 = Vec3(matrix[0] / Sx, matrix[1] / Sx, matrix[2] / Sx);
	Vec3 R1 = Vec3(matrix[4] / Sy, matrix[5] / Sy, matrix[6] / Sy);
	Vec3 R2 = Vec3(matrix[8] / Sz, matrix[9] / Sz, matrix[10] / Sz);

	float sy = sqrt(R0.x * R0.x + R0.y * R0.y);
	bool singular = sy < 1e-6;
	float rotX, rotY, rotZ;
	if (!singular)
	{
		rotX = atan2(R1.z, R2.z);
		rotY = atan2(-R0.z, sy);
		rotZ = atan2(R0.y, R0.x);
	} else
	{
		rotX = atan2(-R2.y, R1.y);
		rotY = atan2(-R0.z, sy);
		rotZ = 0;
	}
	float degX = rotX * 180.0f / M_PIf;
	float degY = rotY * 180.0f / M_PIf;
	float degZ = rotZ * 180.0f / M_PIf;

	rotation = Vec3(degX, degY, degZ);
}

void ColdTable::Transform::DrawToUI()
{
	Vec3 oldPos = position; Vec3 oldScale = scale; Quaternion oldRot = rot;
	if (ImGui::TreeNode("Transform"))
	{
		ImGui::Text("Position:");
		ImGui::PushItemWidth(35);
		ImGui::SameLine();	ImGui::InputFloat("##PosX", &position.x);
		ImGui::SameLine();	ImGui::InputFloat("##PosY", &position.y);
		ImGui::SameLine();	ImGui::InputFloat("##PosZ", &position.z);
		ImGui::PopItemWidth();

		ImGui::Text("Scale:   ");
		ImGui::PushItemWidth(35);
		ImGui::SameLine();	ImGui::InputFloat("##ScaleX", &scale.x);
		ImGui::SameLine();	ImGui::InputFloat("##ScaleY", &scale.y);
		ImGui::SameLine();	ImGui::InputFloat("##ScaleZ", &scale.z);
		ImGui::PopItemWidth();

		Vec3 rotDeg = rot.toEulerAngles();
		ImGui::Text("Rotation:");
		ImGui::PushItemWidth(35);
		ImGui::SameLine();	ImGui::InputFloat("##RotX", &rotDeg.x);
		ImGui::SameLine();	ImGui::InputFloat("##RotY", &rotDeg.y);
		ImGui::SameLine();	ImGui::InputFloat("##RotZ", &rotDeg.z);
		ImGui::PopItemWidth();

		rot = rotDeg.asRotationQuaternion();
		ImGui::TreePop();
	}

	if (ActionManager::Instance != nullptr)
	{
		if (oldPos != position) ActionManager::Instance->PushAction(std::make_unique<EditVec3Action>(&(position), oldPos, position));
		if (oldScale != scale) ActionManager::Instance->PushAction(std::make_unique<EditVec3Action>(&(scale), oldScale, scale));
		if (oldRot != rot) ActionManager::Instance->PushAction(std::make_unique<EditQuatAction>(&(rot), oldRot, rot));
	}
}

void ColdTable::Transform::ProcessReparenting(Transform* parent, Transform* child, bool unlink)
{
	if (parent == nullptr || child == nullptr) return;
	if (unlink)
	{
		if (child->parent != parent) return;

		// Remove child from parent
		for (auto it = parent->children.begin(); it != parent->children.end(); ++it)
		{
			if (*it == child)
			{
				parent->children.erase(it);
				break;
			}
		}

		// Remove parent from child
		child->parent = nullptr;

	} else {
		if (child->parent == parent)
			return;

		// Unlink child from existing parent
		if (child->parent != nullptr)
			child->RemoveParent();

		// Link new parent to child
		child->parent = parent;

		// Add child to parent
		bool alreadyChild = false;
		for (auto it = parent->children.begin(); it != parent->children.end(); ++it)
		{
			if (*it != child)
			{
				alreadyChild = true;
				break;
			} // Already a child
		}
		if (!alreadyChild) parent->children.push_back(child);
	}
}
