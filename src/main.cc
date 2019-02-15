#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <string.h>

#include <buttons.h>
#include <card.h>
#include <gol.h>
#include <power.h>
#include <rtc.h>


constexpr bool	shouldWaitForSerial = false;
const int	UnusedAnalog = A0;


void
seedRandom()
{
	unsigned long	seed = 0;
	pinMode(UnusedAnalog, INPUT);

	for (int i = 0; i < 4; i++) {
		seed += ((analogRead(UnusedAnalog) & 0xF) << 4);
		delay(11);
	}
	randomSeed(seed);
}


void
waitForSerial()
{
	if (shouldWaitForSerial) {
		while (!Serial) ;
	}
}


void
setup()
{
	pinMode(6, INPUT_PULLUP);

	Serial.begin(9600);
	Wire.begin();
	OLED::setup();
	rtcInit();

	waitForSerial();
	Serial.println("BOOT START");
	seedRandom();

	if (!cardInit()) {
		Serial.println("SD INIT FAIL");
		distress();
	}

	Serial.println("BOOT OK");
	Serial.print("BOOT: ");
	Serial.print(millis(), DEC);
	Serial.println("MS");

	OLED::print(10, 0, (const char *)"BOOT OK");
	OLED::print(10, 10, (const char *)"HELLO, WORLD");
	OLED::print(10, 20, (const char *)":)");
	delay(1000);
	OLED::clear();

}


void
loop()
{
	playGameOfLife();
	// If the game loop exits, indicate an error.
	distress();
}
