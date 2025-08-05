#pragma once
#include "ColdTable/Editor/UIScreens/IUIScreen.h"
#include "DearImGUI/imgui.h"
#include <ColdTable/Resource/Texture/Texture.h>

#include "ColdTable/Core/Logger.h"

namespace ColdTable
{
	struct ConsoleLog
	{
		Logger::LogLevel loglevel;
		String message;
	};

	class ConsoleScreen : public IUIScreen
	{
	public:
		ConsoleScreen() : IUIScreen("Console"){};

		void AddLog(Logger::LogLevel loglevel, String message);
		
		virtual void DrawUI() override;

	private:
		Logger::LogLevel loggingLevel = Logger::LogLevel::Error;
		std::vector<ConsoleLog> _logs;
		void ClearLog();

		const char* LogLevelToString(Logger::LogLevel level)
		{
			switch (level)
			{
			case Logger::LogLevel::Error:   return "Error";
			case Logger::LogLevel::Warning: return "Warning";
			case Logger::LogLevel::Info:    return "Info";
			default:                return "Unknown";
			}
		}
	};
}

