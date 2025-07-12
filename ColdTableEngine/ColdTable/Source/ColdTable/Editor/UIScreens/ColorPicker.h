#pragma once
#include <ColdTable/Editor/UIScreens/IUIScreen.h>

namespace ColdTable {

class ColorPicker: public IUIScreen
{

public:
	ColorPicker(std::string screenName);
	void DrawUI() override;
	float color[4];
};
}

