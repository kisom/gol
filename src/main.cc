#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <card.h>
#include <gol.h>


constexpr bool	shouldWaitForSerial = true;
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
	Serial.begin(9600);
	Wire.begin();
	OLED::setup();

	waitForSerial();
	Serial.println("BOOT START");
	seedRandom();

	if (!cardInit()) {
		Serial.println("SD INIT FAIL");
		distress();
	}

	golInit(Random);
	golStore("gol/initial.txt");

	Serial.println("BOOT OK");
	Serial.print("BOOT: ");
	Serial.print(millis(), DEC);
	Serial.println("MS");
	golDisplay();
}


void
loop()
{
	delay(1000);
	golStep();
	golDisplay();
	golStore("gol/current.txt");
}
