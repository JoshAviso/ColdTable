#pragma once
#include <vector>

#include "ColdTable/Core/Core.h"
#include <ColdTable/ECS/GameObjects/GameObject.h>

namespace ColdTable
{
	
class GameObjectManager
{
public:
	static void Initialize();
	static GameObjectPtr CreateGameObject(String objectName);
	static GameObjectPtr FindGameObject(String name);
	static bool RegisterObject(GameObject* gameObject);
	static bool RegisterObject(GameObjectPtr gameObject);
	static bool UnregisterObject(GameObject* gameObject);

	static void ClearAllObjects();

private:
	static GameObjectManager* Instance;
	std::vector<GameObjectPtr> _registeredObjects{};
	float gridSnapping = 0.1f;
	float rotSnapping = 90.0f;
	float scaleSnapping = 1.0f;

	GameObjectManager();
	~GameObjectManager();

	friend class GraphicsEngine;
	friend class HierarchyScreen;
	friend class Camera;
	friend class SelectorTypeScreen;
	friend class SceneManager;
};
}

