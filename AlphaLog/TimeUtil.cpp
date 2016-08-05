#include "TimeUtil.h"
NS_LOGGER_BEGIN
NS_DETAILS_BEGIN


TimeUtil::TimeUtil()
{
}

std::string TimeUtil::Now()
{
	auto now = std::chrono::system_clock::now();
	auto duration = now.time_since_epoch();
	auto mics = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
	auto const usec = mics % (1000 * 1000);
	std::stringstream ss;
	std::time_t t = std::chrono::system_clock::to_time_t(now);
	ss << GetCurrentLocalTime() << "." << std::setw(6) << std::setfill('0') << usec;
	return ss.str();
}

std::string TimeUtil::GetCurrentLocalTime()
{
	
	time_t rawTime = std::time(&rawTime);
	tm* timeInfo = std::localtime(&rawTime);
	char buffer[25] = { '\0' };
	strftime(buffer, 25, "%Y-%m-%d %H-%M-%S", timeInfo);
	return buffer;
}


TimeUtil::~TimeUtil()
{
}

NS_DETAILS_END
NS_LOGGER_END