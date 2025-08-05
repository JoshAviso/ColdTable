#pragma once
#include <ColdTable/Core/Common.h>
#include <map>
#include <vector>

#include "ColdTable/Utility/ISerializeable.h"

namespace ColdTable {

class Scene : public ISerializeable
{
public:
	Scene(String name);

public:
	String SceneName;

	void FromJson(const JsonValue& json) override;
	JsonValue ToJson() const override;

private:
	std::vector<GameObjectPtr> _sceneObjects;

	friend class SceneManager;
};
using ScenePtr = std::shared_ptr<Scene>;
}

