#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <math.h>
#include <string.h>

#include <audio.h>
#include <buttons.h>
#include <card.h>
#include <gol.h>
#include <mandelbrot.h>
#include <noise.h>
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
	asm(".global _printf_float");
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
		OLED::print(0, "SD INIT FAIL");
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
	char	buf[4];
	batteryVoltageString(buf);
	OLED::print(80, 20, buf);
	delay(1000);
	OLED::clear();

}


NoiseGenerator	perlin;

void
loop()
{
	// static double timeStep = 0.0;

	// OLED::clear();
	// for (double j = 0; j < static_cast<double>(OLED::HEIGHT); j++) {
	// 	for (double i = 0; i < static_cast<double>(OLED::WIDTH); i++) {
	// 		double noise = abs(perlin.sample(i, j, timeStep));
	// 		Serial.print(noise);
	// 		Serial.print(" ");
	// 		if (noise > 0.01 || noise < 0.05) {
	// 			OLED::pixel(i, j);
	// 		}
	// 	}
	// 	Serial.println();
	// }
	// OLED::show();
	// timeStep += 0.01;
	// delay(100);

	gol::play(true);
	// mandelbrot();
	// If the game loop exits, indicate an error.
	distress();
}
