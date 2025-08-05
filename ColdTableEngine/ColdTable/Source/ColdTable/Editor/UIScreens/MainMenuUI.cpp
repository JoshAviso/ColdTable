#include "MainMenuUI.h"

#include "ColdTable/ECS/Components/PhysicsComponent.h"
#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Editor/ActionTracking/ActionManager.h"
#include "ColdTable/Resource/ShaderLibrary.h"
#include "ColdTable/Graphics/Renderables/Cube.h"
#include "ColdTable/Resource/Mesh/MeshManager.h"
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
		
		if (ImGui::MenuItem("100 Physics Cubes"))
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
		cube->transform->position.y = 10.0f;
		PhysicsComponent* rb = cube->AddComponent<PhysicsComponent>(1.0f);
		rb->_rigidBody->enableGravity(true);
	}
}
