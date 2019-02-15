#if defined(FEATHER)
#include <feather.h>

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>


#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5



void
setupDisplay()
{
	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);
}


void	
FeatherOLED::setup()
{
	this->oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}


void
FeatherOLED::clear()
{
	this->oled.clearDisplay();
}


void
FeatherOLED::pixel(int x, int y)
{
	this->oled.drawPixel(x, y, WHITE);
}


void
FeatherOLED::clearPixel(int x, int y)
{
	this->oled.drawPixel(x, y, BLACK);
}


void
FeatherOLED::circle(int x, int y, int r)
{
	this->oled.drawCircle((uint16_t)x, (uint16_t)y, (uint16_t)r, WHITE);
}


void
FeatherOLED::show()
{
	this->oled.display();
}


int
FeatherOLED::height()
{
	return 32;
}


int
FeatherOLED::width()
{
	return 128;
}



#endif // defined(FEATHER)
