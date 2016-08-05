#ifndef LOG_STREAM_H
#define LOG_STREAM_H
#include "Pre.h"
#include "Buffer.h"
#include "Noncopyable.h"
#include <string>

NS_LOGGER_BEGIN


class LogStream final : Noncopyable 
{
public:
	using LogBuffer = details::Buffer<details::kSmallBuf>;
	LogStream() = default;
	LogStream &operator << (const bool &b);
	LogStream &operator << (const char &c);
	LogStream &operator << (const char *str);
	LogStream &operator << (const unsigned char *str);
	LogStream &operator << (const std::string &s);

	template<class T>
	LogStream &operator << (const T &value)
	{
		static_assert(std::is_arithmetic<T>::value, "Arithmetic required.");
		if (logBuf_.AvailableSize() >= 32)
		{
			logBuf_.Append(std::to_string(value).c_str(), std::to_string(value).size());
		}
		return *this;
	}

	template<class T>
	LogStream &operator << (const T *const ptr)
	{
		if (ptr != nullptr)
		{
			char ptrStr[10] = { '0','0', '0', '0', '0', '0', '0', '0', '0', '0' };
			::sprintf(ptrStr, "0x%p", ptr);
			logBuf_.Append(ptrStr, 10);
		}
		else
		{
			char ptrStr[7] = { '0','0', '0', '0', '0', '0', '0' };
			::strcpy(ptrStr."nullptr", 7);
			logBuf_.Append(ptrStr,7);
		}
		return *this;
	}

	void Append(const char *data, int len) { logBuf_.Append(data, len); }
	const LogBuffer &GetBuffer()const { return logBuf_; }
	~LogStream();
private:
	LogBuffer logBuf_;
};
NS_LOGGER_END
#endif // !LOGSTREAM_H


