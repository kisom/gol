#ifndef __REDBOARD_H
#define __REDBOARD_H

#ifndef REDBOARD
#error Redboard support should not be included.
#endif

#include <Arduino.h>
#include <Wire.h>


#define Serial	SerialUSB
#define UnusedAnalog	A3


const	int	HEIGHT = 48;
const	int	WIDTH  = 64;


void	setupDisplay();
void	clearDisplay();
void	drawPixel(int x, int y);
void	clearPixel(int x, int y);
void	updateDisplay();


#endif // __REDBOARD_H
