#pragma once
#include "ColdTable/ECS/GameSystems/PhysicsSystem.h"
#include "ColdTable/Editor/UIScreens/IUIScreen.h"
#include "DearImGUI/imgui.h"

namespace ColdTable
{class ScenePlayScreen : public IUIScreen
{
public:
	ScenePlayScreen() : IUIScreen("Scene Play Screen") {}
	void DrawUI() override
	{
		ColdTable::PhysicsSystem::GetInstance()->_isPaused = !_isPlaying;
		if (_isPlaying)
		{
			if (ImGui::Button("Stop"))
			{
				_isPlaying = false;
				ColdTable::PhysicsSystem::GetInstance()->_isPaused = true;
			}
			if (ImGui::Button("Pause"))
			{
				_isPlaying = false;
				ColdTable::PhysicsSystem::GetInstance()->_isPaused = true;
			}
		} else
		{
			if (ImGui::Button("Play"))
			{
				_isPlaying = true;
				ColdTable::PhysicsSystem::GetInstance()->_isPaused = false;
			}
		}
	}

private:
	bool _isPlaying = false;
};
}

