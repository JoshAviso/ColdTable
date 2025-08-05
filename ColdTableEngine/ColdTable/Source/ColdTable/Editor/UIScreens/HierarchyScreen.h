#pragma once
#include "IUIScreen.h"
#include "ColdTable/ECS/GameObjects/GameObject.h"

namespace ColdTable
{
	class HierarchyScreen : public IUIScreen
	{
	public:
		HierarchyScreen();
		void DrawUI() override;

	private:
		void DrawGameObject(GameObject* gameObject, float width);
	};
}

