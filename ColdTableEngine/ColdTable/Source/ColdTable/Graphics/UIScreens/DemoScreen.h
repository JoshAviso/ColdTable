#pragma once
#include <string>

#include "ColdTable/Graphics/UIScreens/IUIScreen.h"
#include "DearImGUI/imgui.h"

class DemoScreen : public ColdTable::IUIScreen
{
private:

public:
	DemoScreen(std::string screenName) : IUIScreen(screenName) {};
	void DrawUI() override
	{
		ImGui::Text("Hello, this is a demo screen!");
	}
};

