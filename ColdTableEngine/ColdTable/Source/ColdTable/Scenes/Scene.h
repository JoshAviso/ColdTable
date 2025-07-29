#pragma once
#include <ColdTable/Core/Common.h>
#include <map>

namespace ColdTable {

class Scene
{
public:
	Scene(String name);

public:
	String SceneName;

	void AddObject(GameObjectPtr object);
	void RemoveObject(GameObjectPtr object);
	void LoadScene();

private:
	std::map<String, GameObjectPtr> _sceneObjects;


};
}

