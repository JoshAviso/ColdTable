#pragma once
#include "ColdTable/Editor/UIScreens/IUIScreen.h"

namespace ColdTable
{
	
class MainMenuUI
{
public:
	static void DrawUI();

private:
	static void AboutMenu();
	static void ToolsMenu();
	static void AddObjectMenu();
	static void SpawnCube();
};
}

