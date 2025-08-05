#include "Scene.h"

#include "ColdTable/ECS/GameObjects/GameObject.h"
#include "ColdTable/Utility/JsonParser.h"

ColdTable::Scene::Scene(String name) : SceneName(name)
{
}

void ColdTable::Scene::FromJson(const JsonValue& json)
{
	SceneName = json["SceneName"].AsString();

	_sceneObjects.clear();
	for (const auto& obj : json["Objects"].arr)
	{
		GameObjectPtr gameObject = std::make_shared<GameObject>("temp");
		if (gameObject)
		{
			gameObject->FromJson(obj);
			_sceneObjects.push_back(gameObject);
		}
	}
}

ColdTable::JsonValue ColdTable::Scene::ToJson() const
{
	JsonValue jsonObj;

	std::vector<JsonValue> objects;
	for (auto obj : _sceneObjects)
		objects.push_back(obj->ToJson());
	
	jsonObj["Objects"] = JsonValue(objects);
	jsonObj["SceneName"] = JsonValue(SceneName);
	return jsonObj;
}

