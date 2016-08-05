#include  "LogImpl.h"
#include <iostream>
#include <string>
#include <map>
#include <cstring>
#include <thread>
#include "log.h"
#include"TimeUtil.h"

NS_LOGGER_BEGIN
NS_DETAILS_BEGIN

std::string GetCurrentThreadID()
{
	std::stringstream ss;
	ss << std::this_thread::get_id();
	return ss.str();
}

const char *GetFileActualName(const char *file)
{
#ifdef WIN32
	auto const split = '\\';
#elif #defined(__linux__)
	auto const split = '/';
#endif
	const char *slash = std::strrchr(file, split);
	return slash ? slash + 1 : nullptr;
}

std::map<LogLevel, std::string> LogLevelMap{
	 std::make_pair(LogLevel::TRACE,"TRACE"),
	 std::make_pair(LogLevel::DEBUG,"DEBUG"),
	 std::make_pair(LogLevel::INFO,"INFO"),
	 std::make_pair(LogLevel::WARN,"WARN"),
	 std::make_pair(LogLevel::ERROR,"ERROR"),
	 std::make_pair(LogLevel::FATAL,"FATAL")
};


LogImpl::LogImpl(LogLevel level, const char * file, int line)
	:logLevel_(level),
	fileName_(file),
	lineNum_(line),
	funcName_(""),
	logStream_()
{
	auto now = details::TimeUtil::Now();
	logStream_ << LogLevelMap[level] << " " << now << " " << details::GetCurrentThreadID() << " ";
}


LogStream & LogImpl::GetLogStream() const
{
	return const_cast<LogStream&>(logStream_);
}

void LogImpl::LogFileAndLine()
{
	if (funcName_.empty())
		logStream_ << " " << details::GetFileActualName(fileName_.c_str()) << ":" << lineNum_ << "\n";
	else
		logStream_ << " " <<funcName_<<" "<< details::GetFileActualName(fileName_.c_str()) << ":" << lineNum_ << "\n";
}

LogImpl::~LogImpl()
{
}
NS_DETAILS_END
NS_LOGGER_END


