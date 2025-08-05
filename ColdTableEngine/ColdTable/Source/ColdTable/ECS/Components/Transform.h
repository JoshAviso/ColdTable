#pragma once
#include <vector>

#include "ColdTable/Editor/IInspectorViewable.h"
#include "ColdTable/Math/Quaternion.h"
#include "ColdTable/Math/Vec3.h"
#include "ColdTable/Utility/ISerializeable.h"

namespace ColdTable
{
	class Transform : public IInspectorViewable, public ISerializeable
	{
	public:
		Vec3 position	= Vec3::Zero;
		Vec3 scale		= Vec3::Identity;
		Quaternion rot = Quaternion::Identity;
		Vec3 rotation	= Vec3::Zero;

		GameObject* gameObject = nullptr;
		Transform* parent = nullptr;
		std::vector<Transform*> children;

		Transform(GameObject* gameObject = nullptr)
			: gameObject(gameObject), parent(nullptr) {
		}
		~Transform() {
			if (parent != nullptr) {
				parent->RemoveChild(this);
			}
			for (auto child : children) {
				child->RemoveParent();
			}
			children.clear();
		}

		void AddParent(Transform* transform);
		void RemoveParent();
		void AddChild(Transform* child);
		void RemoveChild(Transform* child);

		void AddParent(GameObject* parent);
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);


		void FromJson(const JsonValue& json) override;
		JsonValue ToJson() const override;

		Mat4 transformMat() const;
		void setTransfrom(float (&matrix)[16]);

		void DrawToUI() override;

	private:
		static void ProcessReparenting(Transform* parent, Transform* child, bool unlink);
	};
}

