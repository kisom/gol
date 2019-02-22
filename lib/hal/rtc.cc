#include <RTClib.h>
#include <string.h>

#include <hal/rtc.h>


namespace hal {


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


void
rtcFormatTime(char *buf)
{
	DateTime	dto = rtc.now();

	snprintf(buf, 20, "%04d-%02d-%02d %02d:%02d:%02d",
		 dto.year(), dto.month(), dto.day(),
		 dto.hour(), dto.minute(), dto.second());
}


} // namespace hal
