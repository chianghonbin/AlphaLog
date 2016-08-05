#ifndef THREADSAFE_QUEUE_H
#define THREADSAFE_QUEUE_H
#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
#include "Pre.h"
#include "Noncopyable.h"
NS_LOGGER_BEGIN

template<typename T>
class ThreadsafeQueue final : Noncopyable
{
public:
	ThreadsafeQueue() = default;
	T Pop()
	{
		std::unique_lock<std::mutex> lk(mut);
		dataCond_.wait(lk, [this] {return !this->empty(); });
		T ret = std::move(*dataQueue_.front());
		dataQueue_.pop();
		return ret;
	}
	std::shared_ptr<T> PopPtr()
	{
		std::unique_lock<std::mutex> lk(mut);
		dataCond_.wait(lk, [this] {return !this->empty(); });
		std::shared_ptr<T> ret = dataQueue_.front();
		dataQueue_.pop();
		return ret;
	}

	void Push(T value)
	{
		std::shared_ptr<T> data(std::make_shared<T>(std::move(value)));
		std::lock_guard<std::mutex> lk(mut);
		dataQueue_.push(data);
		dataCond_.notify_one();
	}
	bool empty() const
	{
		std::lock_guard<std::mutex> lk(mut);
		return dataQueue_.empty();
	}
private:
	mutable std::mutex mut;
	std::queue<std::shared_ptr<T>> dataQueue_;
	std::condition_variable dataCond_;
};

NS_LOGGER_END
#endif // !THREADSAFE_QUEUE_H
