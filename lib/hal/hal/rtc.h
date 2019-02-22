#ifndef __RTC_H
#define __RTC_H


#include <stdint.h>
#include <RTClib.h>

namespace hal {


bool		rtcInit();
DateTime	rtcNow();
uint32_t	rtcNowUnix();
void		rtcFormatTime(char *);


} // namespae hal
#endif // __RTC_H
