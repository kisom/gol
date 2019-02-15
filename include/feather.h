#ifndef __FEATHER_H
#define __FEATHER_H

#ifndef FEATHER 
#error Feather support should not be included.
#endif


#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#include <graphics.h>


#define UnusedAnalog	A3
#define CardSelect	10

const int	HEIGHT = 32;
const int	WIDTH  = 128;


// Blink the LED to indicate a problem.
void	distress();

// Graphics
void	setupDisplay();
void	clearDisplay();
void	drawPixel(int x, int y);
void	clearPixel(int x, int y);
void	updateDisplay();


class FeatherOLED : public MonoDisplay {
public:
	FeatherOLED() : oled(Adafruit_SSD1306(128, 32, &Wire)) {};
	void	setup();
	void	clear();
	void	pixel(int x, int y);
	void	clearPixel(int x, int y);
	void	circle(int x, int y, int r);
	void	show();
	int	height();
	int	width();
private:
	Adafruit_SSD1306	oled;
};


static FeatherOLED	display;


#endif // __FEATHER_H
