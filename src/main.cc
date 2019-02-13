#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include <gol.h>

void
setup()
{
	Serial.begin(9600);
	Wire.begin();

	display();
}


void
loop()
{

}
