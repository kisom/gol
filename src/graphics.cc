#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <graphics.h>


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


namespace OLED {


// The Adafruit SSD1306 in use is the FeatherWing version.
// 	https://www.adafruit.com/product/2900
Adafruit_SSD1306	oled(128, 32, &Wire);


void
setup()
{
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}


void
clear()
{
	oled.clearDisplay();
}


void
pixel(uint16_t x, uint16_t y)
{
	oled.drawPixel(x, y, WHITE);
}


void
clearPixel(uint16_t x, uint16_t y)
{
	oled.drawPixel(x, y, BLACK);
}


void	
circle(uint16_t x, uint16_t y, uint16_t r, bool fill)
{
	if (fill) {
		oled.fillCircle(x, y, r, WHITE);
	}
	else {
		oled.drawCircle(x, y, r, WHITE);
	}
}


void
show()
{
	oled.display();
}


} // namespace OLED
