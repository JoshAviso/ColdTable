
#include "SceneManager.h"

#include <fstream>

#include "ColdTable/ECS/GameObjects/GameObjectManager.h"
#include "ColdTable/Utility/JsonParser.h"

void ColdTable::SceneManager::CreateScene(String sceneName)
{
	ScenePtr newScene = std::make_shared<Scene>(sceneName);
	_scenes[sceneName] = newScene;
	CurrentScene = newScene;
}

void ColdTable::SceneManager::DeleteScene(String sceneName)
{
	if (_scenes.find(sceneName) == _scenes.end())
	{
		ColdTableLogError("Scene with name '{%s}' does not exist.", sceneName);
		return;
	}
	if (CurrentScene == _scenes[sceneName])
	{
		CurrentScene = nullptr; // Clear current scene if it is being unregistered
	}

	_scenes.erase(sceneName);
}

void ColdTable::SceneManager::LoadScene(String sceneName)
{
	if (_scenes.find(sceneName) == _scenes.end())
	{
		Logger::LogWarning(sceneName);
		Logger::LogError(sceneName);
		ColdTableLogError("Scene with name '{%s}' does not exist.", sceneName);
		return;
	}
	UnloadCurrentScene();
	CurrentScene = _scenes[sceneName];

	// Load logic
	for (auto gameObject : CurrentScene->_sceneObjects)
	{
		if (gameObject != nullptr)
			GameObjectManager::RegisterObject(gameObject->Clone(true));
	}

}

void ColdTable::SceneManager::UnloadCurrentScene()
{
	if (CurrentScene == nullptr)
	{
		ColdTableLogError("No current scene to unload.");
		return;
	}

	// Unload Logic
	GameObjectManager::ClearAllObjects();

	CurrentScene = nullptr;
}

void ColdTable::SceneManager::ReloadCurrentScene()
{
	if (CurrentScene == nullptr)
	{
		ColdTableLogError("No current scene to reload.");
		return;
	}
	LoadScene(CurrentScene->SceneName);
}

void ColdTable::SceneManager::CopyObjectManagerToCurrentScene()
{
	if (CurrentScene == nullptr)
	{
		ColdTableLogError("No current scene to copy objects to.");
		return;
	}
	CurrentScene->_sceneObjects.clear();
	// Copy all registered objects to the current scene
	for (const auto& gameObject : GameObjectManager::Instance->_registeredObjects)
	{
		if (gameObject != nullptr)
			CurrentScene->_sceneObjects.push_back(gameObject->Clone(false));
	}
}

void ColdTable::SceneManager::SaveCurrentScene(const wchar_t* filepath)
{

	if (CurrentScene == nullptr)
	{
		ColdTableLogError("No current scene to save.");
		return;
	}
	CopyObjectManagerToCurrentScene();

	std::wstring path(filepath);

	// Check if path ends with a slash, if not, append one
	if (!path.empty() && path.back() != L'\\' && path.back() != L'/')
	{
		path += L'\\';
	}

	// Convert SceneName (std::string) to wstring
	std::wstring sceneNameW(CurrentScene->SceneName.begin(), CurrentScene->SceneName.end());

	// Append scene name to path
	path += sceneNameW + L".salad";

	// Convert final wide string path to narrow string (assuming UTF-8 compatible)
	std::string finalPath(path.begin(), path.end());

	JsonValue sceneJson = CurrentScene->ToJson();
	std::string jsonString = JsonParser::Serialize(sceneJson, 2);

	std::ofstream file(finalPath);
	if (!file.is_open())
	{
		ColdTableLogError("Failed to open file for saving scene: %s");
		ColdTableLogError(finalPath.c_str());
		return;
	}
	file << jsonString;
	file.close();

	Logger::Log(("Scene " + CurrentScene->SceneName + " saved successfully."));
}

void ColdTable::SceneManager::LoadSceneFromFile(const wchar_t* filepath)
{
	// Open the file for reading
	std::wifstream file(filepath);
	if (!file.is_open())
	{
		ColdTableLogError("Failed to open scene file:");
		size_t size_needed = wcstombs(nullptr, filepath, 0) + 1;
		char* narrowStr = new char[size_needed];
		wcstombs(narrowStr, filepath, size_needed);
		ColdTableLogError(narrowStr);
		delete[] narrowStr;
		return;
	}

	// Unload current scene if it exists
	if (CurrentScene != nullptr)
		UnloadCurrentScene();

	// Read entire file content into a wide string
	std::wstring fileContents((std::istreambuf_iterator<wchar_t>(file)),
		std::istreambuf_iterator<wchar_t>());
	file.close();

	// If you need to convert wide string to narrow string for your JSON parser
	std::string jsonString(fileContents.begin(), fileContents.end());

	try
	{
		// Parse JSON from the string
		size_t i = 0;
		JsonValue sceneJson = JsonParser::ParseObject(jsonString, i);

		// Create a new Scene object and load it from JSON
		Scene scene("Temp");
		scene.FromJson(sceneJson);
		CreateScene(scene.SceneName);
		CurrentScene->FromJson(sceneJson);

	}
	catch (const std::exception& e)
	{
		ColdTableLogError("Error loading scene: %s", e.what());

	}
}

ColdTable::SceneManager* ColdTable::SceneManager::Instance = nullptr;
void ColdTable::SceneManager::Initialize()
{
	if (Instance != nullptr) return;

	Instance = new SceneManager();
}

ColdTable::SceneManager::SceneManager()
{
	CurrentScene = nullptr;
}
