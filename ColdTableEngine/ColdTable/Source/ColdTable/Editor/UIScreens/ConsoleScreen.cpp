#include "ConsoleScreen.h"


void ColdTable::ConsoleScreen::AddLog(Logger::LogLevel loglevel, String message)
{
    _logs.push_back({ loglevel, message });
}

void ColdTable::ConsoleScreen::DrawUI()
{
	const Logger::LogLevel logLevels[] = {Logger::LogLevel::Info, Logger::LogLevel::Warning, Logger::LogLevel::Error};
	if (ImGui::Button("Clear Log"))
	{
		ClearLog();
	}

	ImGui::SameLine(); ImGui::PushItemWidth(100.0f);
	if (ImGui::BeginCombo("##LogLevel", LogLevelToString(loggingLevel)))
	{
		for (auto logLevel : logLevels)
		{
			bool isSelected = logLevel == loggingLevel;
			if (ImGui::Selectable(LogLevelToString(logLevel), isSelected))
			{
				loggingLevel = logLevel;
			}
			if (isSelected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
	ImGui::PopItemWidth(); 

	for (auto log : _logs)
	{
		if (loggingLevel > log.loglevel) continue;

		ImGui::Text(log.message.c_str());
	}
}

void ColdTable::ConsoleScreen::ClearLog()
{
    _logs.clear();
}
