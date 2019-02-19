#include <Arduino.h>

#include <hal/random.h>


namespace hal {


#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
static bool	TRNGReady = false;
static void
enableTRNG()
{
	MCLK->APBCMASK.reg |= MCLK_APBCMASK_TRNG;
	TRNG->CTRLA.reg = TRNG_CTRLA_ENABLE;
	TRNGReady = true;
}
#endif // defined(ADAFRUIT_FEATHER_M4_EXPRESS)


void
seedPRNG(int unusedAnalog)
{
	uint32_t	seed = getHardwareRandomNumber(unusedAnalog);

	randomSeed(seed);
}


uint32_t
getHardwareRandomNumber(int unusedAnalog)
{
	uint32_t	r = 0;

#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
	// The Feather M4 has a TRNG, so we can use that. See chapter 44
	// in the datasheet.
	if (!TRNGReady) {
		enableTRNG();
	}

	// Wait the 84 ABP clock cycles.
	while ((TRNG->INTFLAG.reg & TRNG_INTFLAG_DATARDY) == 0);

	r = TRNG->DATA.reg;
#else
	// Other boards don't have a TRNG, so use the unused
	// analog pin trick.
	pinMode(unusedAnalog, INPUT);

	for (int i = 0; i < 4; i++) {
		r += ((analogRead(unusedAnalog) & 0xF) << 4);
		delay(11);
	}
#endif // defined(ADAFRUIT_FEATHER_M4_EXPRESS)

	return r;	
}


} // namespace hal