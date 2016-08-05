#include "Log.h"
#include "LogImpl.h"

NS_LOGGER_BEGIN

LogLevel GLOBAL_LOGLEVEL = LogLevel::TRACE;
outputCallback GLOBAL_OUTPUT_FUNC = [](const char * msg, int len)
{
	auto n = std::fwrite(msg, 1, static_cast<size_t>(len), stdout);
};
flushCallback GLOBAL_FLUSH_FUNC = []()
{
	fflush(stdout);
};

Log::Log(const char * fileName, int lineNum)
	:logImpl_(LogLevel::INFO,fileName,lineNum)
{
}


Log::Log(const char * fileName, int lineNum, LogLevel level)
	:logImpl_(level,fileName,lineNum)
{
}

Log::Log(const char * fileName, int lineNum, LogLevel level, const char * funcName)
	:logImpl_(level,fileName,lineNum)
{
	logImpl_.LogFuncName(funcName);
}

Log::Log(const char * fileName, int lineNum, bool toAbort)
	:logImpl_(toAbort?LogLevel::ERROR:LogLevel::FATAL,fileName,lineNum)
{
}

Log::~Log()
{
	logImpl_.LogFileAndLine();
	GLOBAL_OUTPUT_FUNC(logImpl_.GetLogStream().GetBuffer().GetBufferData(), logImpl_.GetLogStream().GetBuffer().Length());
	GLOBAL_FLUSH_FUNC();

}

LogStream & Log::GetLogStream() const
{
	return logImpl_.GetLogStream();
	
}

NS_LOGGER_END