#include <util.h>
#include <stdint.h>


void
swap_u8(uint8_t &a, uint8_t &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}


void
swap_ul(unsigned long &a, unsigned long &b)
{
	a ^= b;
	b ^= a;
	a ^= b;
}
