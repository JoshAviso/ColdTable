#include "ColorPicker.h"
#include "DearImGUI/imgui.h"


ColdTable::ColorPicker::ColorPicker(std::string screenName) : IUIScreen(screenName), color()
{
}

void ColdTable::ColorPicker::DrawUI()
{
	ImGui::ColorPicker4("Pick Color", color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_NoInputs);
}
