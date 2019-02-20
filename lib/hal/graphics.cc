#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
#include <string.h>

#include <hal/graphics.h>
#include <hal/power.h>


namespace hal {


const int		pixelPin = 8;
Adafruit_NeoPixel	pixel(1, pixelPin, NEO_GRB + NEO_KHZ800);
static bool		pixelReady = false;


void
distress()
{
	int	led = 13;
	pinMode(led, OUTPUT);
	char	voltage[8];

	neoPixel(255, 0, 0);

	while (true) {
		digitalWrite(led, HIGH);
		delay(100);
		digitalWrite(led, LOW);
		delay(100);
		digitalWrite(led, HIGH);
		delay(100);
		digitalWrite(led, LOW);
		delay(700);
		batteryVoltageString(voltage);
		OLED::print(2, voltage);
		if (Serial) {
			double v = batteryVoltage();
			Serial.print(v, 2);
			Serial.println("V");
		}
	}
}


void
neoPixel(uint8_t r, uint8_t g, uint8_t b)
{
	if (!pixelReady) {
		pixel.begin();
		pixelReady = true;
	}

	pixel.setPixelColor(0, pixel.Color(r, g, b));
	pixel.show();
}


void
neoPixelBrightness(uint8_t brightness)
{
	if (!pixelReady) {
		pixel.begin();
		pixelReady = true;
	}

	pixel.setBrightness(brightness);
	pixel.show();
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


typedef struct {
	char	text[MAX_TEXT+1];	// tested manually
	bool	inverse;
} screenLine;

screenLine	lines[3];

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


void
clearLines()
{
	memset(lines[0].text, 0, MAX_TEXT+1);
	lines[0].inverse = false;
	memset(lines[1].text, 0, MAX_TEXT+1);
	lines[0].inverse = false;
	memset(lines[2].text, 0, MAX_TEXT+1);
	lines[0].inverse = false;
	oled.clearDisplay();
	oled.display();
}


static void
showLines()
{
	oled.clearDisplay();
	for (uint8_t i = 0; i < 3; i++) {
		oled.setCursor(0, i * 10);
		if (lines[i].inverse) {
			oled.setTextColor(BLACK, WHITE);
		}
		else {
			oled.setTextColor(WHITE, BLACK);
		}
		oled.println(lines[i].text);
	}
	oled.display();
}


void
print(uint8_t line, const char *text)
{
	if (line > 2) {
		return;
	}

	int	slen = strnlen(text, MAX_TEXT);

	memset(lines[line].text, 0, MAX_TEXT+1);
	strncpy(lines[line].text, text, slen);
	lines[line].inverse = false;
	showLines();	
}


void
iprint(uint8_t line, const char *text)
{
	if (line > 2) {
		return;
	}

	int	slen = strnlen(text, MAX_TEXT);

	memset(lines[line].text, 0, MAX_TEXT+1);
	strncpy(lines[line].text, text, slen);
	lines[line].inverse = true;
	showLines();	
}


} // namespace OLED
} // namespace hal