#include <ColdTable/Core/Logger.h>
#include <iostream>

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

	std::clog << "[ColdTable-" << logLevelToString(level) << "]: " << message << "\n";
}
