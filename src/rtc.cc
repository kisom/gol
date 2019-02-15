#include <RTClib.h>
#include <rtc.h>


RTC_PCF8523	rtc;

bool
rtcInit()
{
	if (!rtc.begin()) {
		return false;
	}

	if (!rtc.initialized()) {
		return false;
	}

	return true;
}


DateTime
rtcNow()
{
	return rtc.now();
}


uint32_t
rtcNowUnix()
{
	return rtc.now().unixtime();
}
