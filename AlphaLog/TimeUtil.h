#ifndef TIME_UTIL_H
#define TIME_UTIKL_H
#include "Pre.h"
#include <chrono>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>

NS_LOGGER_BEGIN
NS_DETAILS_BEGIN

class TimeUtil
{
public:
	TimeUtil();
	static std::string Now();
	static std::string GetCurrentLocalTime();

	~TimeUtil();
};

NS_DETAILS_END
NS_DETAILS_END
#endif // !TMIE_UTIL_H