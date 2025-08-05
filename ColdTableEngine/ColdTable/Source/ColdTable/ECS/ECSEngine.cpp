#include <string>
#include <ColdTable/ECS/ECSEngine.h>

#include "GameSystems/DebugBlurbSystem.h"
#include "GameSystems/PhysicsSystem.h"

ColdTable::ECSEngine* ColdTable::ECSEngine::Instance = nullptr;
ColdTable::ECSEngine::ECSEngine()
{
	RegisterSystem<DebugBlurbSystem>();
	RegisterSystem<PhysicsSystem>();
}

ColdTable::ECSEngine* ColdTable::ECSEngine::GetInstance()
{
	return Instance;
}

ColdTable::ECSEngine::~ECSEngine()
{

}

bool ColdTable::ECSEngine::RegisterComponent(const ComponentPtr& component)
{
	bool wasInserted = false;
	for (auto componentType : component->ComponentTypes)
	{
		std::vector<ComponentPtr>& componentList = _componentList[componentType];
		auto it = std::find(componentList.begin(), componentList.end(), component);
		if (it != componentList.end())
		{
			Logger::LogWarning(("Component of type " + std::to_string(componentType) + " already exists").c_str());
			continue;
		}

		componentList.push_back(component);
		wasInserted = true;
	}
	return wasInserted;
}

void ColdTable::ECSEngine::UnregisterComponent(const ComponentPtr& component)
{
	for (auto componentType : component->ComponentTypes)
	{
		std::vector<ComponentPtr>& componentList = _componentList[componentType];
		auto it = std::find(componentList.begin(), componentList.end(), component);
		
		if (it != componentList.end())
			componentList.erase(it);
	}
}

void ColdTable::ECSEngine::Initialize()
{
	if (Instance != nullptr) return;

	Instance = new ECSEngine();
}

void ColdTable::ECSEngine::Start()
{
	if (_editorMode != EEditorMode::Playing && !_doFrameStep) return;
	for (const GameSystemPtr& system : _registeredSystems)
	{
		for (auto componentTypes : system->TargetComponentTypes)
		{
			auto it = _componentList.find(componentTypes);
			if (it != _componentList.end())
			{
				system->Start(it->second);
			}
		}
	}
}

void ColdTable::ECSEngine::EarlyUpdate()
{
	if (_editorMode != EEditorMode::Playing && !_doFrameStep) return;
	for (const GameSystemPtr& system : _registeredSystems)
	{
		for (auto componentTypes : system->TargetComponentTypes)
		{
			auto it = _componentList.find(componentTypes);
			if (it != _componentList.end())
			{
				system->EarlyUpdate(it->second);
			}
		}
	}
}

void ColdTable::ECSEngine::Update()
{
	if (_editorMode != EEditorMode::Playing && !_doFrameStep) return;
	for (const GameSystemPtr& system : _registeredSystems)
	{
		for (auto componentTypes : system->TargetComponentTypes)
		{
			auto it = _componentList.find(componentTypes);
			if (it != _componentList.end())
			{
				system->Update(it->second);
			}
		}
	}
}

void ColdTable::ECSEngine::LateUpdate()
{
	if (_editorMode != EEditorMode::Playing && !_doFrameStep) return;
	for (const GameSystemPtr& system : _registeredSystems)
	{
		for (auto componentTypes : system->TargetComponentTypes)
		{
			auto it = _componentList.find(componentTypes);
			if (it != _componentList.end())
			{
				system->LateUpdate(it->second);
			}
		}
	}
}

void ColdTable::ECSEngine::FixedUpdate()
{
	if (_editorMode != EEditorMode::Playing && !_doFrameStep) return;
	for (const GameSystemPtr& system : _registeredSystems)
	{
		for (auto componentTypes : system->TargetComponentTypes)
		{
			auto it = _componentList.find(componentTypes);
			if (it != _componentList.end())
			{
				system->FixedUpdate(it->second);
			}
		}
	}
}

void ColdTable::ECSEngine::Render()
{
	if (_editorMode != EEditorMode::Playing && !_doFrameStep) return;
	for (const GameSystemPtr& system : _registeredSystems)
	{
		for (auto componentTypes : system->TargetComponentTypes)
		{
			auto it = _componentList.find(componentTypes);
			if (it != _componentList.end())
			{
				system->Render(it->second);
			}
		}
	}
}

std::vector<ColdTable::ComponentPtr> ColdTable::ECSEngine::GetComponents(EComponentType type) const
{
	auto it = _componentList.find(type);
	if (it != _componentList.end())
	{
		return it->second;
	}
	return {};
}

template <typename TGameSystem>
std::shared_ptr<TGameSystem> ColdTable::ECSEngine::GetSystem()
{
	static_assert(std::is_base_of<GameSystem, TGameSystem>::value, "TGameSystem must inherit from GameSystem");
	auto it = _systemMap.find(typeid(TGameSystem).name());
	if (it != _systemMap.end())
	{
		return std::dynamic_pointer_cast<TGameSystem>(it->second);
	}
	return nullptr;
}

template <typename TGameSystem>
bool ColdTable::ECSEngine::RegisterSystem()
{
	static_assert(std::is_base_of<GameSystem, TGameSystem>::value, "TGameSystem must inherit from GameSystem");

	auto it = _systemMap.find(typeid(TGameSystem).name());
	if (it != _systemMap.end())
	{
		Logger::Log("GameSystem of already exists");
		return false;
	}

	GameSystemPtr system = std::make_shared<TGameSystem>();
	_registeredSystems.push_back(system);
	_systemMap[typeid(TGameSystem).name()] = system;
	return true;
}
