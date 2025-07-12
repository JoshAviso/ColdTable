#pragma once
#include "IUIScreen.h"
#include "ColdTable/Core/Core.h"
#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Graphics/GraphicsEngine.h"
#include "ColdTable/Graphics/ShaderLibrary.h"
#include "ColdTable/Graphics/Renderables/Cylinder.h"
#include "DearImGUI/imgui.h"

namespace ColdTable
{
	
	class SpawnCylinderScreen : public IUIScreen
	{
	public:
		SpawnCylinderScreen() : IUIScreen("Spawn Cylinder") {};
		virtual void DrawUI() override
		{
			ImGui::Text("Settings:");
			ImGui::SliderInt("Sides", &_sideCount, 5, 360);
			ImGui::SliderFloat("Length", &_length, 0.1f, 100.0f);
			ImGui::SliderFloat("Radius", &_radius, 0.1f, 100.0f);
			ImGui::Checkbox("Horizontal", &_isHorizontal);
			if (ImGui::Button("Spawn"))
			{
				SpawnCylinder();
				ShowScreen = false;
			}
		}

		void SpawnCylinder();
	private:
		int _sideCount = 5;
		float _length = 1.0f;
		float _radius = 0.5f;
		bool _isHorizontal = false;
	};
}

