#pragma once
#include "Component.h"

namespace ColdTable
{
	
	class MaterialComponent : public Component
	{
	public:
		MaterialComponent(GameObjectPtr Owner);
		MaterialComponent(GameObjectPtr Owner, MaterialPtr Material);

		void FromJson(const JsonValue& json) override;
		JsonValue ToJson() const override;

		ComponentPtr Clone(GameObjectPtr newOwner) const override;
		void DrawToUI() override;

	private:
		MaterialPtr _material;
		friend class GraphicsEngine;
		friend class DeviceContext;

	};
	using MaterialComponentPtr = std::shared_ptr<MaterialComponent>;
}

