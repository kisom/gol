#include <Arduino.h>
#include <stdlib.h>
#include <string.h>
#include <sam.h>

#include <hal/power.h>
#include <util.h>


namespace hal {


// Note: on the Feather M0, the battery voltage divider is on the same 
// pin as the OLED FeatherWing's button A, so it needs to be reset to 
// the INPUT_PULLUP mode after a reading.


double
batteryVoltage()
{
	double	voltage;

#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
	int	batteryPin = A6;
#elif defined(ADAFRUIT_FEATHER_M0)
	int	batteryPin = 9;
#else
#error Unknown board configuration - unable to build power library.
#endif
	pinMode(batteryPin, INPUT);
	delay(5); // Give time for the pin to settle.
	voltage = static_cast<double>(analogRead(batteryPin));
#if defined(ADAFRUIT_FEATHER_M0)
	pinMode(9, INPUT_PULLUP);
#endif

	// First, multiply by 2, then multiply by the reference voltage
	// of 3.3V, then divide by 1024.
	return voltage / 155.15;
}


void
batteryVoltageString(char *buf)
{
	double	voltage = batteryVoltage();

	sprintf(buf, "%4.2fV", voltage);
}


void
sleep()
{
    // Enable standby sleep mode (deepest sleep) and activate.
    // Insights from Atmel ASF library.
#if (SAMD20 || SAMD21)
    // Don't fully power down flash when in sleep
    NVMCTRL->CTRLB.bit.SLEEPPRM = NVMCTRL_CTRLB_SLEEPPRM_DISABLED_Val;
#endif
#if defined(__SAMD51__)
    PM->SLEEPCFG.bit.SLEEPMODE = 0x4;         // Standby sleep mode
    while(PM->SLEEPCFG.bit.SLEEPMODE != 0x4); // Wait for it to take
#else
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
#endif

    __DSB(); // Data sync to ensure outgoing memory accesses complete
    __WFI(); // Wait for interrupt (places device in sleep mode)

    // Code resumes here on wake (WDT early warning interrupt).
    return;
}


} // namespace hal