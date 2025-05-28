#pragma once
#include <memory>

namespace ColdTable
{
	class Logger final
	{
	public:
		enum class LogLevel
		{
			Error = 0,
			Warning,
			Info
		};

		static std::unique_ptr<Logger> shared_instance;
		static void Initialize(LogLevel loglevel);

		explicit Logger(LogLevel logLevel = LogLevel::Error);
		~Logger();
		static void Log(LogLevel level, const char* message);

	protected:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator = (const Logger&) = delete;
		Logger& operator = (Logger&&) = delete;

	private:
		LogLevel _logLevel = LogLevel::Error;
	};

#define ColdTableLogInfo(message)\
	Logger::Log((Logger::LogLevel::Info), message);\

#define ColdTableLogWarning(message)\
	Logger::Log((Logger::LogLevel::Warning), message);\

#define ColdTableLogError(message)\
	Logger::Log((Logger::LogLevel::Error), message);\

#define ColdTableLogErrorAndThrow(message)\
	{\
		ColdTableLogError(message);\
		throw std::runtime_error(message);\
	}\

}

