#pragma once
#include "Component.h"

namespace ColdTable
{
	
	class MeshComponent : public Component
	{
	public:
		MeshComponent(GameObjectPtr Owner);
		MeshComponent(GameObjectPtr Owner, MeshPtr Mesh);

		void FromJson(const JsonValue& json) override;
		JsonValue ToJson() const override;

		ComponentPtr Clone(GameObjectPtr newOwner) const override;
		void DrawToUI() override;

		MeshPtr Mesh;
	};

	using MeshComponentPtr = std::shared_ptr<MeshComponent>;
}

