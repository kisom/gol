#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Streaming.h>

#include <board.h>
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

	int	die = random(6);
	Serial << "DIE: " << die << endl;
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
	setupDisplay();

	waitForSerial();
	seedRandom();
	initGame(Random);

	Serial << "BOOT OK" << endl;
	Serial << "BOOT: " << millis() << "MS" << endl;
	display();
}


void
loop()
{
	step();
	display();
	delay(100);
}
