#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <string.h>

#include <audio.h>
#include <buttons.h>
#include <card.h>
#include <gol.h>
#include <mandelbrot.h>
#include <power.h>
#include <random.h>
#include <rtc.h>


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
	pinMode(6, INPUT_PULLUP);

	Serial.begin(9600);
	Wire.begin();
	OLED::setup();
	neoPixel(0, 0, 150);
	neoPixelBrightness(10);
	rtcInit();
	audioSetup();

	waitForSerial();
	seedPRNG(UnusedAnalog);

	if (!cardInit()) {
		OLED::print(0, 0, "SD INIT FAIL");
		distress();
	}

	Serial.println("BOOT OK");
	Serial.print("BOOT: ");
	Serial.print(millis(), DEC);
	Serial.println("MS");

	OLED::print(10, 0, (const char *)"BOOT OK");
	OLED::print(10, 10, (const char *)"HELLO, WORLD");
#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
	OLED::print(10, 20, "FEATHER M4");
#elif defined(ADAFRUIT_FEATHER_M0)
	OLED::print(10, 20, "FEATHER M0");
#else
	OLED::print(10, 20, "UNK FEATHER");
#endif
	delay(1000);
	OLED::clear();

}


void
loop()
{
	// playGameOfLife();
	mandelbrot();
	// If the game loop exits, indicate an error.
	distress();
}
