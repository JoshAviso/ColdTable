#pragma once
#include <vector>

#include "ColdTable/Core/Core.h"
#include <ColdTable/ECS/GameObjects/GameObject.h>

namespace ColdTable
{
	
class GameObjectManager
{
public:
	static GameObjectPtr CreateGameObject(String objectName);
	static bool RegisterObject(GameObject* gameObject);
	static bool UnregisterObject(GameObject* gameObject);

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
};
}

