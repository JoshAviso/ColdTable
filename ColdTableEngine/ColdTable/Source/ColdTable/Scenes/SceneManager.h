#pragma once

namespace ColdTable {
	class SceneManager
	{
	public:
		void RegisterScene();
		


	public:
		static SceneManager* Instance;
		static void Initialize();
	private:
		SceneManager();

	};
}

