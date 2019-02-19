#ifndef __RANDOM_H
#define __RANDOM_H


#include <stdint.h>


namespace hal {


uint32_t	getHardwareRandomNumber(int unusedAnalog);
void		seedPRNG(int unusedAnalog);


} // namespace hal
#endif // __RANDOM_H
