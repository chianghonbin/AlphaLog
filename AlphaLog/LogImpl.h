#ifndef LOG_IMPL_H
#define LOG_IMPL_H
#include "Pre.h"
#include "Noncopyable.h"
#include "LogStream.h"


NS_LOGGER_BEGIN
enum class LogLevel;
NS_DETAILS_BEGIN
class LogImpl final :Noncopyable
{
public:
	LogImpl(LogLevel level, const char *file, int line);
	LogStream & GetLogStream() const;
	void LogFileAndLine();
	void LogFuncName(const char *func)
	{
		funcName_ = func;
	}
	LogLevel GetLogLevel() const
	{
		return logLevel_;
	}
	~LogImpl();
private:
	LogStream logStream_;
	LogLevel logLevel_;
	std::string fileName_;
	int lineNum_;
	std::string funcName_;
};

NS_DETAILS_END
NS_LOGGER_END
#endif // !LOGIMPL_H