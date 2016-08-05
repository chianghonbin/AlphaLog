#ifndef LOG_H
#define LOG_H
#include <functional>
#include "Noncopyable.h"
#include "Pre.h"
#include "LogImpl.h"

NS_LOGGER_BEGIN

using outputCallback = std::function<void(const char* msg, int len)>;
using flushCallback = std::function<void(void)>;
enum class LogLevel { TRACE, DEBUG, INFO, WARN, ERROR, FATAL, LOG_LEVEL_NUM };
extern LogLevel GLOBAL_LOGLEVEL;
extern outputCallback GLOBAL_OUTPUT_FUNC;
extern flushCallback GLOBAL_FLUSH_FUNC;

class LogStream;

class Log final:Noncopyable
{
public:
	Log(const char *fileName, int lineNum);
	Log(const char *fileName, int lineNum, LogLevel level);
	Log(const char *fileName, int lineNum, LogLevel level, const char* funcName);
	Log(const char *fileName, int lineNum, bool toAbort);
	~Log();
public:
	static LogLevel GetGlobalLogLevel()
	{
		return Logger::GLOBAL_LOGLEVEL;
	}
	static void SetOutputCallbackFunc(outputCallback outcb)
	{
		GLOBAL_OUTPUT_FUNC = outcb;
	}
	static void SetFlushCallbackFunc(flushCallback flushcb)
	{
		GLOBAL_FLUSH_FUNC = flushcb;
	}
	static void SetGlobalLogLevel(LogLevel level)
	{
		GLOBAL_LOGLEVEL = level;
	}

	LogStream& GetLogStream() const;

private:
	details::LogImpl logImpl_;

};

NS_LOGGER_END

#define LOG_TRACE if (Logger::Log::GetGlobalLogLevel() <= Logger::LogLevel::TRACE) \
	(Logger::Log(__FILE__, __LINE__, Logger::LogLevel::TRACE, __FUNCTION__).GetLogStream())

#define LOG_DEBUG if (Logger::Log::GetGlobalLogLevel() <= Logger::LogLevel::DEBUG) \
	Logger::Log(__FILE__, __LINE__, Logger::LogLevel::DEBUG, __FUNCTION__).GetLogStream()

#define LOG_INFO if (Logger::Log::GetGlobalLogLevel() <= Logger::LogLevel::INFO) \
	(Logger::Log(__FILE__, __LINE__).GetLogStream())

#define LOG_WARN Logger::Log(__FILE__, __LINE__, Logger::LogLevel::WARN).GetLogStream()
#define LOG_ERROR Logger::Log(__FILE__, __LINE__, Logger::LogLevel::ERROR).GetLogStream()
#define LOG_FATAL Logger::Log(__FILE__, __LINE__, Logger::LogLevel::FATAL).GetLogStream()
#define LOG_SYSERR Logger::Log(__FILE__, __LINE__, false).GetLogStream()
#define LOG_SYSFATAL Logger::Log(__FILE__, __LINE__, true).GetLogStream()
#endif // !LOG_H

