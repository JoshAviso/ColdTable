#include "MainMenuUI.h"

#include "ColdTable/ECS/Components/PhysicsComponent.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Resource/ShaderLibrary.h"
#include "ColdTable/Graphics/Renderables/Cube.h"
#include "ColdTable/Resource/Mesh/MeshManager.h"
#include "ColdTable/Scenes/SceneManager.h"
#include "ColdTable/Utility/Utils.h"
#include "DearImGUI/imgui.h"

void ColdTable::MainMenuUI::DrawUI()
{
	if (ImGui::BeginMainMenuBar())
	{
		AboutMenu();
		EditMenu();
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

void ColdTable::MainMenuUI::EditMenu()
{
	if (ImGui::BeginMenu("Edit"))
	{
		ActionManager* actionManager = ActionManager::Instance;
		bool canUndo = actionManager != nullptr && actionManager->_undoQueue.size() > 0;
		bool canRedo = actionManager != nullptr && actionManager->_redoQueue.size() > 0;
		if (ImGui::MenuItem("Undo", NULL, false, canUndo))
		{
			actionManager->Undo();
		}
		if (ImGui::MenuItem("Redo", NULL, false, canRedo))
		{
			actionManager->Redo();
		}
		ImGui::EndMenu();
	}
}

char ColdTable::MainMenuUI::sceneFileToLoad[] = "";
char ColdTable::MainMenuUI::sceneSavePath[] = "";
void ColdTable::MainMenuUI::ToolsMenu()
{
	if (ImGui::BeginMenu("Tools"))
	{
		if (ImGui::MenuItem("Color Picker"))
		{
			IUIScreen* colorPicker = EditorUIManager::GetScreen("Color Picker").get();
			if (colorPicker) colorPicker->ShowScreen = !colorPicker->ShowScreen;
		}
		ImportMenu();
		ExportMenu();
		ImGui::EndMenu();
	}
}

void ColdTable::MainMenuUI::ExportMenu()
{
	EEditorMode editorMode = ECSEngine::GetInstance()->_editorMode;
	ImGui::BeginDisabled(editorMode != EEditorMode::Editing);
	if (ImGui::BeginMenu("Export Scene"))
	{
		ImGui::Text("Export Location:"); ImGui::SameLine();
		ImGui::InputText("##ExportTextbox", sceneSavePath, IM_ARRAYSIZE(sceneSavePath));
		struct stat info;
		ImGui::BeginDisabled(
			sceneSavePath == nullptr || sceneSavePath[0] == '\0' ||
			stat(sceneSavePath, &info) != 0
		);
		if (ImGui::Button("Export"))
		{
			size_t len = strlen(sceneSavePath);
			wchar_t* wBuffer = new wchar_t[len + 1];
			mbstowcs(wBuffer, sceneSavePath, len + 1);
			SceneManager::Instance->SaveCurrentScene(wBuffer);
			delete[] wBuffer;
		}
		ImGui::EndDisabled();

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}

void ColdTable::MainMenuUI::ImportMenu()
{
	EEditorMode editorMode = ECSEngine::GetInstance()->_editorMode;
	ImGui::BeginDisabled(editorMode != EEditorMode::Editing);
	if (ImGui::BeginMenu("Import Scene"))
	{
		ImGui::Text("Import Path:"); ImGui::SameLine();
		ImGui::InputText("##ImportTextbox", sceneFileToLoad, IM_ARRAYSIZE(sceneFileToLoad));
		size_t len = strlen(sceneFileToLoad);
		struct stat info;
		ImGui::BeginDisabled(sceneFileToLoad == nullptr || sceneFileToLoad[0] == '\0' || 
			strcmp(sceneFileToLoad + len - 6, ".salad") != 0 ||
			stat(sceneFileToLoad, &info) != 0
		);
		if (ImGui::Button("Import"))
		{
			wchar_t* wBuffer = new wchar_t[len + 1];
			mbstowcs(wBuffer, sceneFileToLoad, len + 1);
			SceneManager::Instance->LoadSceneFromFile(wBuffer);
			SceneManager::Instance->ReloadCurrentScene();
			delete[] wBuffer;
		}
		ImGui::EndDisabled();

		ImGui::EndMenu();
	}
	ImGui::EndDisabled();
}

void ColdTable::MainMenuUI::AddObjectMenu()
{
	if (ImGui::BeginMenu("Spawn Object"))
	{

		if (ImGui::MenuItem("Empty GameObject"))
		{
			GameObjectPtr plane = GameObjectManager::CreateGameObject("GameObject");
			/*
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Cylinder").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
			*/
		}
		if (ImGui::MenuItem("Plane"))
		{
			GameObjectPtr plane = GameObjectManager::CreateGameObject("Plane");
			plane->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Plane"));
			/*
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Cylinder").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
			*/
		}
		if (ImGui::MenuItem("Cube"))
		{
			SpawnCube();
		}
		if (ImGui::MenuItem("Sphere"))
		{
			GameObjectPtr sphere = GameObjectManager::CreateGameObject("Sphere");
			sphere->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Sphere"));
			/*
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Cylinder").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
			*/
		}

		if (ImGui::MenuItem("Cylinder"))
		{
			GameObjectPtr cylinder = GameObjectManager::CreateGameObject("Cylinder");
			cylinder->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Cylinder"));
			/*
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Cylinder").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
			*/
		}


		if (ImGui::MenuItem("Capsule"))
		{
			GameObjectPtr capsule = GameObjectManager::CreateGameObject("Capsule");
			capsule->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Capsule"));
			/*
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Cylinder").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
			*/
		}
		/*
		if (ImGui::MenuItem("Stairs"))
		{
			IUIScreen* spawnMenu = EditorUIManager::GetScreen("Spawn Stairs").get();
			if (spawnMenu) spawnMenu->ShowScreen = !spawnMenu->ShowScreen;
		}
		*/
		
		if (ImGui::MenuItem("60 Physics Cubes"))
		{
			SpawnPhysicsCubes(60);
		}
		

		ImGui::EndMenu();
	}
}

void ColdTable::MainMenuUI::SpawnCube()
{
	GameObjectPtr cube = GameObjectManager::CreateGameObject("Cube");
	cube->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Cube"));
}

void ColdTable::MainMenuUI::SpawnPhysicsCubes(int count)
{

	for (int i = 0; i < count; i++)
	{
		GameObjectPtr cube = GameObjectManager::CreateGameObject("Cube");
		cube->AddComponent<MeshComponent>(MeshManager::Instance->GetMesh("Cube"));
		cube->transform->position.y = Utils::Random(8.0f, 15.0f);
		cube->transform->position.x = Utils::Random(-5.0f, 5.0f);
		cube->transform->position.z = Utils::Random(-5.0f, 5.0f);
		PhysicsComponent* rb = cube->AddComponent<PhysicsComponent>(1.0f);
		rb->_rigidBody->enableGravity(true);
	}
}


