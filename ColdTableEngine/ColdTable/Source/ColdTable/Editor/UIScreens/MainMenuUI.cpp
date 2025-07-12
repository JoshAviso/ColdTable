#include "MainMenuUI.h"

#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Graphics/ShaderLibrary.h"
#include "ColdTable/Graphics/Renderables/Cube.h"
#include "DearImGUI/imgui.h"

void ColdTable::MainMenuUI::DrawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		AboutMenu();
		ToolsMenu();
		AddObjectMenu();
		ImGui::EndMainMenuBar();
	}
}

void ColdTable::MainMenuUI::AboutMenu()
{
	if (ImGui::BeginMenu("About"))
	{
		if (ImGui::MenuItem("Credits"))
		{
			IUIScreen* credits = EditorUIManager::GetScreen("Credits").get();
			if (credits) credits->ShowScreen = true;
		}

		ImGui::EndMenu();
	}
}

void ColdTable::MainMenuUI::ToolsMenu()
{
	if (ImGui::BeginMenu("Tools"))
	{
		if (ImGui::MenuItem("Color Picker"))
		{
			IUIScreen* colorPicker = EditorUIManager::GetScreen("Color Picker").get();
			if (colorPicker) colorPicker->ShowScreen = !colorPicker->ShowScreen;
		}
		ImGui::EndMenu();
	}
}

void ColdTable::MainMenuUI::AddObjectMenu()
{
	if (ImGui::BeginMenu("Spawn Object"))
	{
		if (ImGui::MenuItem("Cube"))
		{
			SpawnCube();
		}

		if (ImGui::MenuItem("Cylinder"))
		{
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Cylinder").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
		}

		if (ImGui::MenuItem("Stairs"))
		{
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Stairs").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
		}

		ImGui::EndMenu();
	}
}

void ColdTable::MainMenuUI::SpawnCube()
{
	GameObjectPtr cube = GameObjectManager::CreateGameObject("Cube");
	cube->renderable = std::make_shared<Cube>(GraphicsEngine::Instance->CreateIndexBuffer(), ShaderLibrary::GetShader("BlankShader"));
	
}
