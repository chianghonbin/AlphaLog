#include "LogStream.h"
#include <cstring>
NS_LOGGER_BEGIN




LogStream & LogStream::operator<<(const bool & b)
{
	logBuf_.Append(b ? "true" : "false", 5);
	return *this;
}

LogStream & LogStream::operator<<(const char & c)
{
	logBuf_.Append(&c, 1);
	return *this;
}

LogStream & LogStream::operator<<(const char * str)
{
	if (str)
	{
		logBuf_.Append(str, std::strlen(str));
	}
	else
	{
		logBuf_.Append("nullstring", 10);
	}
	return *this;
}

LogStream & LogStream::operator<<(const unsigned char * str)
{
	return operator << (reinterpret_cast<const char *>(str));
}

LogStream & LogStream::operator<<(const std::string & s)
{
	logBuf_.Append(s.c_str(), s.size());
	return *this;
}

LogStream::~LogStream()
{
}
NS_LOGGER_END