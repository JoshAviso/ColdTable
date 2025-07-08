#pragma once
#include <string>

namespace ColdTable
{
	class IUIScreen
	{
	public:
		IUIScreen(std::string screenName) : _screenName(screenName) {};

		void Render();

	public:
		bool ShowScreen = true;

	protected:
		std::string _screenName;
		virtual void DrawUI() = 0;
	};
}

