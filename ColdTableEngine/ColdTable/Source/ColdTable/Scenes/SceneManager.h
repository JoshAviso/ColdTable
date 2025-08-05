#pragma once
#include <unordered_map>

#include "Scene.h"
#include "ColdTable/Core/Core.h"

namespace ColdTable {
	class SceneManager
	{
	public:
		void CreateScene(String sceneName);
		void DeleteScene(String sceneName);

		void LoadScene(String sceneName);
		void UnloadCurrentScene();
		void ReloadCurrentScene();

		ScenePtr CurrentScene;
		void CopyObjectManagerToCurrentScene();
		void SaveCurrentScene(const wchar_t* filepath);
		void LoadSceneFromFile(const wchar_t* filepath);

		static SceneManager* Instance;
		static void Initialize();
	private:
		SceneManager();

		std::unordered_map<String, ScenePtr> _scenes;

	};
}

