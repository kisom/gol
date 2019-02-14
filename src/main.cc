#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Streaming.h>

#include <board.h>
#include <card.h>
#include <gol.h>


constexpr bool	shouldWaitForSerial = false;


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
	pinMode(A0, OUTPUT);
	setupDisplay();

	waitForSerial();
	seedRandom();

	if (!cardInit(CardSelect)) {
		Serial << "Failed to initialise SD card on pin "
		       << CardSelect << endl;
		distress();
	}

	golInit(Random);

	Serial << "BOOT OK" << endl;
	Serial << "BOOT: " << millis() << "MS" << endl;
	golDisplay();
}


void
loop()
{
	delay(10);
	golStep();
	golDisplay();
}
