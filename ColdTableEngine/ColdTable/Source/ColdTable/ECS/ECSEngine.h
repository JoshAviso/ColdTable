#pragma once  
#include <map>  
#include <vector>  
#include <ColdTable/Core/Base.h>  
#include <ColdTable/ECS/GameSystems/GameSystem.h>  

namespace ColdTable {
	enum EEditorMode
	{
		Playing, Editing, Paused
	};

	class ECSEngine  
	{  
	public:
		static ECSEngine* GetInstance();
		virtual ~ECSEngine();  

	public:
		bool RegisterComponent(const ComponentPtr& component);
		void UnregisterComponent(const ComponentPtr& component);

		static void Initialize();
		void Start();
		void EarlyUpdate();
		void Update();  
		void LateUpdate();
		void FixedUpdate();
		void Render();

		template <typename TGameSystem>
		std::shared_ptr<TGameSystem> GetSystem();

		std::vector<ComponentPtr> GetComponents(EComponentType type) const;

		template <typename TGameSystem>  
		bool RegisterSystem();  

	private:
		EEditorMode											_editorMode = EEditorMode::Editing;
		friend class ScenePlayScreen;
		bool												_doFrameStep = false;
		friend class GameLoop;

		std::vector<GameSystemPtr>							_registeredSystems;  
		std::map<String, GameSystemPtr>						_systemMap;
		std::map<EComponentType, std::vector<ComponentPtr>> _componentList;

		static ECSEngine* Instance;
		ECSEngine();  
	};  

}
