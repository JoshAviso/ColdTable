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
	static void EditMenu();
	static void ToolsMenu();
	static void ExportMenu();
	static void ImportMenu();
	static void AddObjectMenu();
	static void SpawnCube();
	static void SpawnPhysicsCubes(int count);

	static char sceneFileToLoad[512];
	static char sceneSavePath[512];
};
}

