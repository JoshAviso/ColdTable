#include "GameObject.h"

#include "GameObjectManager.h"
#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/ECSEngine.h"
#include "ColdTable/Graphics/VertexBuffer.h"
#include "ColdTable/Graphics/Renderables/Renderable.h"
#include "ColdTable/Utility/JsonParser.h"
#include "DearImGUI/imgui.h"

ColdTable::GameObject::GameObject(String name): name(name), renderable(0), transform(new Transform(this))
{
}

ColdTable::GameObjectPtr ColdTable::GameObject::Clone(bool registerComponents)
{
	GameObjectPtr newObject = std::make_shared<GameObject>(this->name);
	newObject->transform = new Transform();
	newObject->transform->position = transform->position;
	newObject->transform->scale = transform->scale;
	newObject->transform->rot = transform->rot;
	
	for (auto child : transform->children)
	{
		if (child == nullptr) continue;
		if (child->gameObject == nullptr) continue;
		GameObjectPtr childObj = GameObjectManager::FindGameObject(child->gameObject->name);
		if (childObj == nullptr) continue;

		childObj->transform->AddParent(newObject.get());
	}
	if (transform->parent != nullptr)
	{
		if (transform->parent->gameObject != nullptr)
		{
			GameObjectPtr parent = GameObjectManager::FindGameObject(transform->parent->gameObject->name);
			if (parent != nullptr)
				newObject->transform->AddParent(parent.get());
		}
	}
	

	// Clone components
	for (const auto& component : _components)
	{
		if (component != nullptr)
		{
			auto clonedComponent = component->Clone(newObject);
			if (clonedComponent != nullptr)
			{
				newObject->_components.push_back(clonedComponent);
				if (registerComponents)
					ECSEngine::GetInstance()->RegisterComponent(clonedComponent);
			}
		}
	}
	return newObject;
}

void ColdTable::GameObject::Destroy(GameObject* gameObject)
{
	if (gameObject) gameObject->Destroy();
	else Logger::Log(Logger::LogLevel::Error, "Attempted to destroy a null GameObject.");
}

void ColdTable::GameObject::Destroy()
{
	GameObjectManager::UnregisterObject(this);
	for (auto component : _components)
	{
		Component::Destroy(component);
	}
}

ColdTable::GameObject::~GameObject()
{
	delete transform;
}

void ColdTable::GameObject::FromJson(const JsonValue& json)
{
	name = json["Name"].AsString();
	enabled = json["Enabled"].AsBool();
	transform->FromJson(json["Transform"]);

	std::vector<JsonValue> componentJsons = json["Components"].arr;
	for (auto componentJson : componentJsons)
	{
		ComponentPtr component = Component::MakeFromJson(componentJson);
		component->Owner = shared_from_this(); // Set the owner of the component to this GameObject
		_components.push_back(component);
	}
}

ColdTable::JsonValue ColdTable::GameObject::ToJson() const
{
	JsonValue jsonObj;
	jsonObj["Transform"] = transform->ToJson();
	jsonObj["Enabled"] = JsonValue(enabled);
	jsonObj["Name"] = JsonValue(name);

	std::vector<JsonValue> componentJsons;
	for (auto component : _components)
	{
		componentJsons.push_back(component->ToJson());
	}

	jsonObj["Components"] = JsonValue(componentJsons);
	return jsonObj;
}

void ColdTable::GameObject::DrawToUI()
{
	ImGui::Checkbox(name.c_str(), &enabled);
	transform->DrawToUI();
	for (auto component : _components)
	{
		if (component != nullptr)
			component->DrawToUI();
	}
}

void ColdTable::GameObject::Translate(Vec3 translation)
{
	transform->position += translation;
	Logger::Log(Logger::LogLevel::Info, ("GameObject " + name + " translation off " + transform->position.toString()).c_str());
}

void ColdTable::GameObject::Rotate(Vec3 axis, float degree)
{
	transform->rotation += axis * degree;
}

void ColdTable::GameObject::Scale(Vec3 scale)
{
	for (auto face : renderable->_vertexBuffer->_faceObjects)
	{
		face->Scale(scale);
	}
}
