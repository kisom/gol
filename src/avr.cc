#if defined(AVR)

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#include <SFE_MicroOLED.h> 
#include <avr.h>


MicroOLED oled(9, 1);


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
setupDisplay()
{
	oled.begin();
}


void
clearDisplay()
{
	oled.clear(ALL);
	oled.clear(PAGE);
}


void
drawPixel(int x, int y)
{
	oled.pixel(x, y);
}


void
clearPixel(int x, int y)
{
	oled.pixel(x, y, BLACK, NORM);
}


void
updateDisplay()
{
	oled.display();
}


#endif // defined(AVR)
