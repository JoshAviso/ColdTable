#pragma once

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

		explicit Logger(LogLevel logLevel = LogLevel::Error);
		~Logger();
		void Log(LogLevel level, const char* message);

	protected:
		Logger(const Logger&) = delete;
		Logger(Logger&&) = delete;
		Logger& operator = (const Logger&) = delete;
		Logger& operator = (Logger&&) = delete;

	private:
		LogLevel _logLevel = LogLevel::Error;
	};

#define ColdTableLogInfo(message)\
	getLogger().Log((Logger::LogLevel::Info), message);\

#define ColdTableLogWarning(message)\
	getLogger().Log((Logger::LogLevel::Warning), message);\

#define ColdTableLogError(message)\
	getLogger().Log((Logger::LogLevel::Error), message);\

#define ColdTableLogErrorAndThrow(message)\
	{\
	ColdTableLogError(message);\
	throw std::runtime_error(message);\
	}\

}

