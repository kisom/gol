#if defined(FEATHER)
#include <feather.h>

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>


Adafruit_SSD1306	oled(128, 32, &Wire);

#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5


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
	oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	pinMode(BUTTON_A, INPUT_PULLUP);
	pinMode(BUTTON_B, INPUT_PULLUP);
	pinMode(BUTTON_C, INPUT_PULLUP);
}


void
clearDisplay()
{
	oled.clearDisplay();
}


void
drawPixel(int x, int y)
{
	oled.drawPixel(x, y, WHITE);
}


void
clearPixel(int x, int y)
{
	oled.drawPixel(x, y, BLACK);
}


void
updateDisplay()
{
	oled.display();
}


#endif // defined(FEATHER)
