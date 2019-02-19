#ifndef __RANDOM_H
#define __RANDOM_H


#include <stdint.h>


uint32_t	getHardwareRandomNumber(int unusedAnalog);
void		seedPRNG(int unusedAnalog);


#endif // __RANDOM_H
