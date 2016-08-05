#include "AsyncLogging.h"
#include <functional>
NS_LOGGER_BEGIN

AsyncLogging::AsyncLogging()
	:loggingThread_(std::bind(&AsyncLogging::LoggingThreadFuncCallBack, this))
{
}


AsyncLogging::~AsyncLogging()
{
}

void AsyncLogging::Append(const char * msg, uint64_t len)
{
}

void AsyncLogging::Flush()
{
}

void AsyncLogging::LoggingThreadFuncCallBack()
{
}
NS_LOGGER_END