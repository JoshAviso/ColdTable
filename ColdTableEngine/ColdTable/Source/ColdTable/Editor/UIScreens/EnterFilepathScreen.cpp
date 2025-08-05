#include "EnterFilepathScreen.h"

#include <algorithm>

void ColdTable::EnterFilepathScreen::DrawUI()
{
	ImGui::Text("Enter Filepath: "); ImGui::SameLine();
	ImGui::InputText("##Text Input", _filepath, sizeof(_filepath));
}

ColdTable::String ColdTable::EnterFilepathScreen::ReadFilepath()
{
	String output = _filepath;
	_filepath[0] = '\0';
	return output;
}
