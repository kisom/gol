#if defined(REDBOARD)

#include <Arduino.h>
#include <Wire.h>

#include <SFE_MicroOLED.h> 
#include <redboard.h>


MicroOLED oled(9, 1);


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


#endif // defined(REDBOARD)
