#include <util/util.h>
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


uint16_t
clamp_u16(uint16_t v, uint16_t max)
{
	if (v >= max) {
		return max - 1;
	}
	return v;
}


uint16_t
dclamp_u16(uint16_t v, int16_t dv, uint16_t max)
{
	if ((dv < 0) && (static_cast<uint16_t>(-dv) > v)) {
		return 0;
	}

	v += dv;
	if (v >= max) {
		v = max - 1;
	}

	return v;
}
