#ifndef __UTIL_H
#define __UTIL_H


#include <stdint.h>


void	 swap_u8(uint8_t &a, uint8_t &b);
void	 swap_ul(unsigned long &a, unsigned long &b);

uint16_t	clamp_u16(uint16_t v, uint16_t max);
uint16_t	dclamp_u16(uint16_t v, int16_t dv, uint16_t max);


#endif // __UTIL_H
