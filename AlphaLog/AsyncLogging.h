#ifndef ASYNC_LOGGING_H
#define ASYNC_LOGGING_H
#include <thread>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include "Pre.h"
#include "Buffer.h"
#include "ThreadsafeQueue.h"
#include <chrono>

NS_LOGGER_BEGIN

class AsyncLogging final : Noncopyable
{
public:
	AsyncLogging();
	~AsyncLogging();
	void Append(const char* msg, uint64_t len);
	void Flush();

private:
	void LoggingThreadFuncCallBack();

private:
	std::thread loggingThread_;
	details::Buffer<details::kLargeBuf> currentBuffer_;
	details::Buffer<details::kLargeBuf> nextBuffer_;
	std::atomic<bool> currentBufferFullFlag_{ false };
	std::condition_variable bufferFullCond_;
	std::mutex bufferFullMutex_;
	std::mutex mut_;
	std::chrono::system_clock::time_point lastFlushTime_;
	using LogBufferType = details::Buffer<details::kLargeBuf>;
	using LogQueueType = ThreadsafeQueue<LogBufferType>;
	const int FLUSH_INTERVAL = 3;
	LogQueueType logQueue_;
};

NS_LOGGER_END
#endif // !ASYNC_LOGGING_H


