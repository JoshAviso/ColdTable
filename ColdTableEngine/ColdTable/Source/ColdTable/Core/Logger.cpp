#include <ColdTable/Core/Logger.h>
#include <iostream>

#include "ColdTable/Editor/EditorUIManager.h"
#include "ColdTable/Editor/UIScreens/ConsoleScreen.h"

std::unique_ptr<ColdTable::Logger> ColdTable::Logger::shared_instance = nullptr;

void ColdTable::Logger::Initialize(LogLevel loglevel)
{
	if (shared_instance == nullptr)
		shared_instance = std::make_unique<Logger>(loglevel);
}

ColdTable::Logger::Logger(LogLevel logLevel): _logLevel(logLevel)
{
	std::clog << "Cold Table Engine" << "\n";
	std::clog << "-----------------" << "\n";
}

ColdTable::Logger::~Logger()
{

}

void ColdTable::Logger::Log(LogLevel level, const char* message)
{
	if (shared_instance == nullptr)
	{
		std::clog << "[ColdTable-ERROR]: Attempting to log while logger is not initialized." << "\n";
		throw std::runtime_error("[ColdTable-ERROR]: Attempting to log while logger is not initialized.");
	}

	auto logLevelToString = [](LogLevel level)
		{
			switch (level)
			{
			case LogLevel::Error:	return "ERROR";
			case LogLevel::Warning: return "WARN";
			case LogLevel::Info:	return "INFO";
			default:				return "Unknown";
			}
		};

	if (level > shared_instance->_logLevel) return;

	String output = "[" + std::string(logLevelToString(level)) + "]: " + message;

	ConsoleScreen* console = dynamic_cast<ConsoleScreen*>(EditorUIManager::GetScreen("Console").get());
	if (console != nullptr) console->AddLog(level, output);
	else std::clog << output.c_str() << "\n";
}

void ColdTable::Logger::Log(const char* message)
{
	Log(LogLevel::Info, message);
}

void ColdTable::Logger::LogWarning(const char* message)
{
	Log(LogLevel::Warning, message);
}

void ColdTable::Logger::LogError(const char* message)
{
	Log(LogLevel::Error, message);
}

void ColdTable::Logger::Log(std::string message)
{
	Log(message.c_str());
}

void ColdTable::Logger::LogWarning(std::string message)
{
	LogWarning(message.c_str());
}

void ColdTable::Logger::LogError(std::string message)
{
	LogError(message.c_str());
}
