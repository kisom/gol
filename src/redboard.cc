#if defined(REDBOARD)

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <stdint.h>

#include <SFE_MicroOLED.h> 
#include <redboard.h>
#include <graphics.h>


MicroOLED	oled(9, 1);

void
distress()
{
	int	led = 13;
	pinMode(led, OUTPUT);

	while (true) {
		digitalWrite(led, HIGH);
		delay(100);
		digitalWrite(led, LOW);
		delay(100);
		digitalWrite(led, HIGH);
		delay(100);
		digitalWrite(led, LOW);
		delay(700);
	}
}

void
SFE_MicroOLED::setup()
{
	oled = MicroOLED(9, 1);
	oled.begin();
}


void
SFE_MicroOLED::clear()
{
	oled.clear(ALL);
	oled.clear(PAGE);
}


void
SFE_MicroOLED::pixel(int x, int y)
{
	oled.pixel(x, y);
}


void
SFE_MicroOLED::clearPixel(int x, int y)
{
	oled.pixel(x, y, BLACK, NORM);
}


void
SFE_MicroOLED::circle(int x, int y, int r)
{
	oled.circle((uint8_t)x, (uint8_t)y, (uint8_t)r);
}


void
SFE_MicroOLED::show()
{
	oled.display();
}


int
SFE_MicroOLED::height()
{
	return HEIGHT;
}


int
SFE_MicroOLED::width()
{
	return WIDTH;
}


#endif // defined(REDBOARD)
