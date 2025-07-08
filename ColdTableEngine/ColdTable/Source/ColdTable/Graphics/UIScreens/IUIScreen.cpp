#include "IUIScreen.h"

#include "DearImGUI/imgui.h"

void ColdTable::IUIScreen::Render()
{
	if (!ShowScreen) return;

	ImGui::Begin(_screenName.c_str());
	DrawUI();
	ImGui::End();
}
