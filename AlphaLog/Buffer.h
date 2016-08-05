#ifndef BUFFER_H
#define BUFFER_H
#include <cstring>
#include "Pre.h"
#include "Noncopyable.h"

NS_LOGGER_BEGIN
NS_DETAILS_BEGIN

const int kSmallBuf = 4000;
const int kLargeBuf = 4000 * 1000;

template<int SIZE>
class Buffer final : Noncopyable
{
public:
	Buffer() :cur_(buffer_)
	{
		std::memset(buffer_, 0, SIZE);
	}
	~Buffer()
	{
	}

	Buffer(Buffer &&rhs) noexcept
	{
		std::memcpy(this->buffer_, rhs->buffer_, static_cast<size_t>(rhs.Length()));
		this->cur_ += rhs->Length();
		std::memset(rhs.buffer_, 0, SIZE);
		rhs->cur_ = rhs->buffer_;
	}
	Buffer &&operator=(Buffer &&rhs) noexcept
	{
		if (this != &rhs)
		{
			std::memcpy(this->buffer_, rhs->buffer_, static_cast<size_t>(rhs.Length()));
			this->cur_ += rhs->Length();
			std::memset(rhs.buffer_, 0, SIZE);
			rhs->cur_ = rhs->buffer_;
		}
		return *this;
	}

	bool Append(const char *msg, int msglen)
	{
		auto ret = (std::memcpy(cur_, msg, static_cast<size_t>(msglen)) != nullptr);
		cur_ += msglen;
		return ret;
	}

	int Length() const
	{
		return cur_ - buffer_;
	}

	int AvailableSize() const
	{
		return buffer_ + SIZE - cur_;
	}

	const char *GetBufferData()const
	{
		return buffer_;
	}
	void Clear()
	{
		std::memset(buffer_, 0, SIZE);
		cur_ = buffer_;
	}

	bool Empty() const
	{
		return cur_ == buffer_;
	}
private:
	char buffer_[SIZE];
	char* cur_;
};

NS_DETAILS_END
NS_LOGGER_END
#endif // !BUFFER_H


