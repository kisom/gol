#ifndef __REDBOARD_H
#define __REDBOARD_H

#ifndef REDBOARD
#error Redboard support should not be included.
#endif

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>

#include <graphics.h>


#define Serial	SerialUSB
#define UnusedAnalog	A3
#define CardSelect	10


const	int	HEIGHT = 48;
const	int	WIDTH  = 64;


// Blink the LED to indicate a problem.
void	distress();


// The SFE_MicroOLED is an SSD-1306-based OLED. It comes in both
// a breakout package as well as a QWIIC package.
class SFE_MicroOLED : public MonoDisplay {
public:
	SFE_MicroOLED() {};
	void	setup();
	void	clear();
	void	pixel(int x, int y);
	void	clearPixel(int x, int y);
	void	circle(int x, int y, int r);
	void	show();
	int	height();
	int	width();
};


static SFE_MicroOLED	display;


#endif // __REDBOARD_H
