#pragma once
#include "ColdTable/Graphics/UIScreens/IUIScreen.h"
#include "DearImGUI/imgui.h"

namespace ColdTable
{
	
	class AboutScreen : public IUIScreen
	{
	public:
		AboutScreen() : IUIScreen("Credits") {};

		virtual void DrawUI() override
		{
			ImGui::Text("Cold Table Editor ver 0.0.1");
			ImGui::Text("Developed by: Josiah Kurt B. Aviso");
			ImGui::Separator();
			ImGui::Text("A simple game engine and editor created in DirectX11.");
			if (ImGui::Button("Close"))
			{
				ShowScreen = false;
			}
		}
	};
}

