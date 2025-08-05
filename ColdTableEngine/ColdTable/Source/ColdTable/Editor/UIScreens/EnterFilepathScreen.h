#pragma once
#include "IUIScreen.h"
#include "ColdTable/Core/Core.h"
#include "DearImGUI/imgui.h"

namespace ColdTable
{
	
	class EnterFilepathScreen : public IUIScreen
	{
	public:
		EnterFilepathScreen() : IUIScreen("Enter Filepath") {};
		virtual void DrawUI() override;

		String ReadFilepath();

	private:
		char _filepath[256] = "";
	};
}

