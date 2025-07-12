#include "GameObjectManager.h"

#include <string>

#include "ColdTable/Core/Logger.h"


ColdTable::GameObjectManager* ColdTable::GameObjectManager::Instance = nullptr;

ColdTable::GameObjectPtr ColdTable::GameObjectManager::CreateGameObject(String objectName)
{
	if (Instance == nullptr) Instance = new GameObjectManager();

	bool foundDuplicate = false;
	int duplicateCount = 0;
	do
	{
		foundDuplicate = false;
		for (auto gameObject : Instance->_registeredObjects)
		{
			if (duplicateCount == 0)
			{
				if (gameObject->name == objectName)
				{
					foundDuplicate = true;
					duplicateCount++;
					break;
				}
			}
			else
			{
				if (gameObject->name == (objectName + " (" + std::to_string(duplicateCount) + ")"))
				{
					foundDuplicate = true;
					duplicateCount++;
					break;
				}
			}
		}
	} while (foundDuplicate);
	if (duplicateCount != 0)
		objectName = objectName + " (" + std::to_string(duplicateCount) + ")";

	GameObjectPtr objectPtr = std::make_shared<GameObject>(objectName);

	auto itr = std::find(Instance->_registeredObjects.begin(), Instance->_registeredObjects.end(), objectPtr);
	if (itr != Instance->_registeredObjects.end()) return nullptr;

	Instance->_registeredObjects.push_back(objectPtr);
	return objectPtr;
}

bool ColdTable::GameObjectManager::RegisterObject(GameObject* gameObject)
{
	if (Instance == nullptr) Instance = new GameObjectManager();

	GameObjectPtr objectPtr = std::make_shared<GameObject>(*gameObject);

	auto itr = std::find(Instance->_registeredObjects.begin(), Instance->_registeredObjects.end(), objectPtr);
	if (itr != Instance->_registeredObjects.end()) return false;

	Instance->_registeredObjects.push_back(objectPtr);
	return true;
}

bool ColdTable::GameObjectManager::UnregisterObject(GameObject* gameObject)
{
	if (Instance == nullptr) return false;

	/*auto itr = std::find(Instance->_registeredObjects.begin(), Instance->_registeredObjects.end(), gameObject);
	if (itr == Instance->_registeredObjects.end()) return false;

	Instance->_registeredObjects.erase(itr);*/
	return true;
}

ColdTable::GameObjectManager::GameObjectManager()
{
	_registeredObjects.clear();
}

ColdTable::GameObjectManager::~GameObjectManager()
{
	_registeredObjects.clear();
}
