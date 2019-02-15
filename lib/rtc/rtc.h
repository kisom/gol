#ifndef __RTC_H
#define __RTC_H


#include <stdint.h>
#include <RTClib.h>


bool		rtcInit();
DateTime	rtcNow();
uint32_t	rtcNowUnix();


#endif // __RTC_H
