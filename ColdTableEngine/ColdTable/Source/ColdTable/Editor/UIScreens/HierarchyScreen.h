#pragma once
#include "IUIScreen.h"

namespace ColdTable
{
	class HierarchyScreen : public IUIScreen
	{
	public:
		HierarchyScreen();
		void DrawUI() override;
	};
}

