#ifndef __REDBOARD_H
#define __REDBOARD_H

#ifndef REDBOARD
#error Redboard support should not be included.
#endif

#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <Wire.h>


#define Serial	SerialUSB
#define UnusedAnalog	A3
#define CardSelect	9


const	int	HEIGHT = 48;
const	int	WIDTH  = 64;


// Blink the LED to indicate a problem.
void	distress();

// Graphics
void	setupDisplay();
void	clearDisplay();
void	drawPixel(int x, int y);
void	clearPixel(int x, int y);
void	updateDisplay();


#endif // __REDBOARD_H
