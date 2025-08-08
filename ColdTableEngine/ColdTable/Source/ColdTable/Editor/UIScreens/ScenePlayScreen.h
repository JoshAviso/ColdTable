#pragma once
#include "ColdTable/ECS/ECSEngine.h"
#include "ColdTable/ECS/GameSystems/PhysicsSystem.h"
#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Editor/UIScreens/IUIScreen.h"
#include "ColdTable/Scenes/SceneManager.h"
#include "DearImGUI/imgui.h"

namespace ColdTable
{

class ScenePlayScreen : public IUIScreen
{
public:
	ScenePlayScreen() : IUIScreen("Scene Play Screen") {}
	void DrawUI() override
	{
		EEditorMode editorMode = ECSEngine::GetInstance()->_editorMode;

		//SceneManager::Instance->SaveCurrentScene(L"D:\\OneDrive\\Downloads");
		//SceneManager::Instance->LoadSceneFromFile(L"D:\\OneDrive\\Downloads\\DefaultScene.salad");

		if (editorMode == EEditorMode::Editing && ImGui::Button("Play"))
		{
			EditorUIManager::Instance->InspectorSelected = nullptr;
			SceneManager::Instance->CopyObjectManagerToCurrentScene();
			ECSEngine::GetInstance()->_editorMode = EEditorMode::Playing;
		}

		if ((editorMode == EEditorMode::Playing || editorMode == EEditorMode::Paused)
			&& ImGui::Button("Stop"))
		{
			EditorUIManager::Instance->InspectorSelected = nullptr;SceneManager::Instance->ReloadCurrentScene();
			ECSEngine::GetInstance()->_editorMode = EEditorMode::Editing;
		}

		ImGui::SameLine();
		if (editorMode == EEditorMode::Playing && ImGui::Button("Pause"))
			ECSEngine::GetInstance()->_editorMode = EEditorMode::Paused;

		ImGui::SameLine();
		if (editorMode == EEditorMode::Paused && ImGui::Button("Resume"))
			ECSEngine::GetInstance()->_editorMode = EEditorMode::Playing;
		
		ImGui::SameLine();
		if (editorMode == EEditorMode::Paused && ImGui::Button("Frame Step"))
		{
			ECSEngine::GetInstance()->_doFrameStep = true;
		}
	}
};
}

