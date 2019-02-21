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
#include <menu.h>
#include <walker.h>


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
	waitForSerial();
	Serial.println("BOOT STARTS");

	Wire.begin();

	hal::OLED::setup();
	hal::neoPixel(0, 0, 150);
	hal::neoPixelBrightness(10);
	hal::rtcInit();
	hal::audioSetup();

	hal::seedPRNG(UnusedAnalog);

	if (!hal::card::init()) {
		hal::OLED::print(0, "SD INIT FAIL");
		hal::distress();
	}

	Serial.println("BOOT OK");
	Serial.print("BOOT: ");
	Serial.print(millis(), DEC);
	Serial.println("MS");

	hal::OLED::print(0, "BOOT OKAY");
	hal::OLED::iprint(1, "HELLO, WORLD");
#if defined(ADAFRUIT_FEATHER_M4_EXPRESS)
	char	buf[20] = "FEATHER M4 - ";
#elif defined(ADAFRUIT_FEATHER_M0)
	char	buf[20] = "FEATHER M0 - ";
#else
	char	buf[20] = "FEATHER ?? - ";
#endif
	hal::batteryVoltageString(buf+13);
	hal::OLED::print(2, buf);
	delay(1000);
	hal::OLED::print(1, "HELLO, WORLD");
	delay(250);
	hal::OLED::iprint(1, "HELLO, WORLD");
	delay(250);
	hal::OLED::print(1, "HELLO, WORLD");
	delay(250);
	hal::OLED::iprint(1, "HELLO, WORLD");
	delay(250);
	hal::OLED::clear();
	hal::OLED::clearLines();

	menu::addItem("GAME OF LIFE", gol::play);
	menu::addItem("WALKER", walker::play);
	menu::addItem("MANDELBROT", mandelbrot);
	menu::addItem("DISTRESS", hal::distress);
	menu::addItem("SLEEP", hal::sleep);

	// Cut the neopixel to save power.
	hal::neoPixel(0, 0, 0);
	hal::neoPixelBrightness(0);
}


void
loop()
{
	menu::show();
	hal::distress();
}
