#pragma once
#include "ColdTable/Editor/UIScreens/IUIScreen.h"
#include "DearImGUI/imgui.h"
#include <ColdTable/Resource/Texture/Texture.h>

namespace ColdTable
{
	
	class AboutScreen : public IUIScreen
	{
	public:
		AboutScreen() : IUIScreen("Credits") , _logo(0){};

		void SetLogo(TexturePtr logo);
		
		virtual void DrawUI() override;

	private:
		TexturePtr _logo;
	};
}

