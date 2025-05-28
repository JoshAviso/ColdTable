#include <ColdTable/ECS/ECSEngine.h>

ColdTable::ECSEngine::ECSEngine(const ECSEngineDesc& desc) : Base(desc.base)
{

}

ColdTable::ECSEngine::~ECSEngine()
{
	for (auto object : _registeredObjects)
		delete object;
	for (auto system : _registeredSystems) 
		delete system;
}

// Called at the very start of the game
void ColdTable::ECSEngine::Start()
{

}

void ColdTable::ECSEngine::OnInput()
{

}

void ColdTable::ECSEngine::Update()
{

}

void ColdTable::ECSEngine::LateUpdate()
{

}

void ColdTable::ECSEngine::Render()
{
}

void ColdTable::ECSEngine::RegisterObject(GameObject& object)
{
	_registeredObjects.push_back(&object);
}

void ColdTable::ECSEngine::RegisterSystem(GameSystem& system)
{
	_registeredSystems.push_back(&system);
}
