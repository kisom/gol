#include <Arduino.h>
#include <stdlib.h>
#include <string.h>

#include <hal/power.h>
#include <util.h>


// Note: the battery voltage divider is on the same pin as the
// OLED FeatherWing's button A, so it needs to be reset to the
// INPUT_PULLUP mode after a reading.


double
batteryVoltage()
{
	double	voltage;

#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
	int	batteryPin = A6;
#elif defined(ADAFRUIT_FEATHER_M0)
	int	batteryPin = 9;
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
