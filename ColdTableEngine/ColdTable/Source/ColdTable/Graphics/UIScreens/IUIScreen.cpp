#include "IUIScreen.h"

#include "DearImGUI/imgui.h"

void ColdTable::IUIScreen::Render()
{
	ImGui::Begin(_screenName.c_str());
	DrawUI();
	ImGui::End();
}
