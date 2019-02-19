#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <math.h>
#include <string.h>

#include <hal/audio.h>
#include <hal/buttons.h>
#include <hal/card.h>
#include <hal/graphics.h>
#include <hal/power.h>
#include <hal/random.h>
#include <hal/rtc.h>

#include <gol.h>
#include <mandelbrot.h>
#include <noise.h>


constexpr bool	shouldWaitForSerial = false;
const int	UnusedAnalog = A0;


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
	asm(".global _printf_float");
	pinMode(6, INPUT_PULLUP);

	Serial.begin(9600);
	Wire.begin();
	hal::OLED::setup();
	hal::neoPixel(0, 0, 150);
	hal::neoPixelBrightness(10);
	hal::rtcInit();
	hal::audioSetup();

	waitForSerial();
	hal::seedPRNG(UnusedAnalog);

	if (!hal::card::init()) {
		hal::OLED::print(0, "SD INIT FAIL");
		hal::distress();
	}

	Serial.println("BOOT OK");
	Serial.print("BOOT: ");
	Serial.print(millis(), DEC);
	Serial.println("MS");

	hal::OLED::print(10, 0, (const char *)"BOOT OK");
	hal::OLED::print(10, 10, (const char *)"HELLO, WORLD");
#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
	hal::OLED::print(10, 20, "FEATHER M4");
#elif defined(ADAFRUIT_FEATHER_M0)
	hal::OLED::print(10, 20, "FEATHER M0");
#else
	hal::OLED::print(10, 20, "UNK FEATHER");
#endif
	char	buf[4];
	hal::batteryVoltageString(buf);
	hal::OLED::print(80, 20, buf);
	delay(1000);
	hal::OLED::clear();

}


NoiseGenerator	perlin;

void
loop()
{
	gol::play(true);
	// mandelbrot();
	// If the game loop exits, indicate an error.
	hal::distress();
}
