#pragma once
#include <vector>
#include <ColdTable/Core/Base.h>
#include <ColdTable/ECS/GameObjects/GameObject.h>
#include <ColdTable/ECS/GameSystems/GameSystem.h>

namespace ColdTable {
	class ECSEngine : public Base
	{
	public:
		explicit ECSEngine(const ECSEngineDesc& desc);
		virtual ~ECSEngine() override;

	public:
		void Start();
		void OnInput();
		void Update();
		void LateUpdate();
		void Render();

	private:
		std::vector<GameObject*> _registeredObjects;
		std::vector<GameSystem*> _registeredSystems;

		void RegisterObject(GameObject& object);
		void RegisterSystem(GameSystem& system);
	};
}

