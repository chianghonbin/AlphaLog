#ifndef FILE_UTIL_H
#define FILE_UTIL_H
#include "Pre.h"
#include <cstdio>
#include <mutex>
#include <memory>
#include "Noncopyable.h"
#include <atomic>
#include <functional>
NS_LOGGER_BEGIN
NS_DETAILS_BEGIN

class FileUtil final : Noncopyable
{
public:
	FileUtil(const char *fileName);
	void AppendLogFile(const char *msg, int len);
	void FlushLogFile();
	int GetWritesBytes() const { return writedBytes_; }

	~FileUtil();
private:
	int WriteLogFile(const char *msg, int len);
	std::string	GetLogFileName();
private:
	std::unique_ptr<FILE, std::function<int(FILE*)>> logFilePtr_;
	std::mutex mut_;
	std::atomic<int> writedBytes_;
	char buffer_[64 * 1024];
};

NS_DETAILS_END
NS_LOGGER_END
#endif // !FILE_UTIL_H


