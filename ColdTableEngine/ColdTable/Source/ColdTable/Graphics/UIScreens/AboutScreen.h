#pragma once
#include "ColdTable/Graphics/UIScreens/IUIScreen.h"
#include "DearImGUI/imgui.h"
#include <ColdTable/Resource/Texture/Texture.h>

namespace ColdTable
{
	
	class AboutScreen : public IUIScreen
	{
	public:
		AboutScreen(TexturePtr logoTex) : IUIScreen("Credits") , _logo(logoTex){};

		virtual void DrawUI() override
		{
			if(_logo != nullptr)
				ImGui::Image((void*)_logo->_resourceView, ImVec2(_logo->Width, _logo->Height));
			ImGui::Text("Cold Table Editor ver 0.0.1");
			ImGui::Text("Developed by: Josiah Kurt B. Aviso");
			ImGui::Separator();
			ImGui::Text("A simple game engine and editor created in DirectX11.");
			ImGui::Separator();

			ImGui::Text("Acknowledgements:");
			ImGui::Text("PardCode - Game Engine Programming YouTube series");
			ImGui::Text("Dr. Neil Patrick Del Gallego - GDENG03 Professor");
			if (ImGui::Button("Close"))
			{
				ShowScreen = false;
			}
		}

	private:
		TexturePtr _logo;
	};
}

