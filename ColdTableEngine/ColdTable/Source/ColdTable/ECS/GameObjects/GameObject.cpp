#include "GameObject.h"

#include "GameObjectManager.h"
#include "ColdTable/Core/Logger.h"
#include "ColdTable/ECS/ECSEngine.h"
#include "ColdTable/Graphics/VertexBuffer.h"
#include "ColdTable/Graphics/Renderables/Renderable.h"

ColdTable::GameObject::GameObject(String name): name(name), renderable(0), transform(new Transform())
{
}

void ColdTable::GameObject::Destroy(GameObject* gameObject)
{
	if (gameObject) gameObject->Destroy();
	else Logger::Log(Logger::LogLevel::Error, "Attempted to destroy a null GameObject.");
}

void ColdTable::GameObject::Destroy()
{
	GameObjectManager::UnregisterObject(this);
}

ColdTable::GameObject::~GameObject()
{
	delete transform;
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

void ColdTable::GameObject::AddComponent(ComponentPtr component)
{
	component->Owner = std::make_shared<GameObject>(*this);
	_components.push_back(component);
	ECSEngine::GetInstance()->RegisterComponent(component);
}
