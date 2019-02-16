#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <math.h>

#include <graphics.h>
#include <rtc.h>


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


uint16_t
delta(uint16_t a, uint16_t b)
{
	if (a < b) {
		return b - a;
	}
	return a - b;
}


double
euclidist(Point &a, Point &b)
{
	uint32_t	dx, dy;

	dx = delta(a.x, b.x);
	dx *= dx;

	dy = delta(a.y, b.y);
	dy *= dy;
	
	return sqrt(static_cast<double>(dy + dx));
}

namespace OLED {


// The Adafruit SSD1306 in use is the FeatherWing version.
// 	https://www.adafruit.com/product/2900
Adafruit_SSD1306	oled(128, 32, &Wire);


void
setup()
{
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	oled.setTextSize(1);
	oled.setTextColor(WHITE);        // Draw white text
	oled.clearDisplay();
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
print(uint16_t x, uint16_t y, const char *text)
{
	oled.setCursor(x, y);
	oled.print(text);
	oled.display();
}


void
print(uint16_t x, uint16_t y, double value, int precision)
{
	oled.setCursor(x, y);
	oled.print(value, precision);
	oled.display();
}


void
show()
{
	oled.display();
}


} // namespace OLED
