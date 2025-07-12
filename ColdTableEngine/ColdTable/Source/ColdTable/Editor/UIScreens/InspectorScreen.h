#pragma once
#include "ColdTable/Editor/UIScreens/IUIScreen.h"

namespace ColdTable
{
	
class InspectorScreen : public IUIScreen
{
public:
	InspectorScreen();
	void DrawUI() override;
};
}

