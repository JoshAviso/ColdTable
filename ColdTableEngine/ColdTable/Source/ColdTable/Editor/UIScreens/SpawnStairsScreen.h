#pragma once
#include "IUIScreen.h"
#include "DearImGUI/imgui.h"

namespace ColdTable
{
	
	class SpawnStairsScreen : public IUIScreen
	{
	public:
		SpawnStairsScreen() : IUIScreen("Spawn Stairs") {};
		virtual void DrawUI() override;

	private:
		bool _editingPerStepSettings = false;
		int _stepCount = 2;
		float _height = 1.0f;
		float _length = 1.0f;
		float _width = 1.0f;
		float _stepHeight = 0.5f;
		float _stepDepth = 0.5f;

		void UpdateStepStats();
		void UpdateShapeStats();
		void SpawnStairs();
	};
}

