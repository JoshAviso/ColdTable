#include <ColdTable/Core/Logger.h>
#include <iostream>

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

	if (level > _logLevel) return;

	std::clog << "[ColdTable-" << logLevelToString(level) << "]: " << message << "\n";
}
