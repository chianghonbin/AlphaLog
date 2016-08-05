#include "FileUtil.h"
#include <cstdio>
#include <mutex>
#include <memory>
#include <assert.h>

NS_LOGGER_BEGIN
NS_DETAILS_BEGIN


FileUtil::FileUtil(const char * fileName)
	:logFilePtr_(std::fopen(fileName,"a+"),std::fclose)
{
	assert(logFilePtr_.get());
	std::setbuf(logFilePtr_.get(), buffer_);
}

void FileUtil::AppendLogFile(const char * msg, int len)
{
	auto writedBytes = WriteLogFile(msg, len);
	auto remain = len - writedBytes;
	while (remain > 0)
	{
		auto writed = WriteLogFile(msg + writedBytes, len);
		if (writed == 0)
			if (std::ferror(logFilePtr_.get()))
				break;
		writedBytes += writed;
		remain -= writed;
	}
}

void FileUtil::FlushLogFile()
{
	std::fflush(logFilePtr_.get());
}

FileUtil::~FileUtil()
{
}

int FileUtil::WriteLogFile(const char * msg, int len)
{
#ifdef WIN32 
	return ::_fwrite_nolock(msg, 1, len, logFilePtr_.get());
#elif defined(__linux__)
	return ::fwrite_unlocked(msg, 1, len, logFilePtr_.get());
#endif
}

std::string FileUtil::GetLogFileName()
{
	return std::string();
}


NS_DETAILS_END
NS_LOGGER_END