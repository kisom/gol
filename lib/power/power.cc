#include <Arduino.h>
#include <power.h>


// Note: the battery voltage divider is on the same pin as the
// OLED FeatherWing's button A, so it needs to be reset to the
// INPUT_PULLUP mode after a reading.
const int	batteryPin = 9;


double
batteryVoltage()
{
	double	voltage;

	pinMode(batteryPin, INPUT);
	delay(5); // Give time for the pin to settle.
	voltage = static_cast<double>(analogRead(batteryPin));
	pinMode(batteryPin, INPUT_PULLUP);

	// First, multiple by 2, then multiply by the reference voltage
	// of 3.3V, then divide by 1024.
	return voltage / 155.15;
}
