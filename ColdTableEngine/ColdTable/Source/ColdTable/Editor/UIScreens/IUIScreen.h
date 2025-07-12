#pragma once
#include <string>

namespace ColdTable
{
	class IUIScreen
	{
	public:
		IUIScreen(std::string screenName) : ScreenName(screenName) {}
		virtual ~IUIScreen() = default;

	public:
		bool ShowScreen = true;
		std::string ScreenName;
		int RenderPriority = 0;
		
	protected:
		virtual void DrawUI() = 0;

		friend class GraphicsEngine;
	};
}

