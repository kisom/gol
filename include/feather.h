#ifndef __FEATHER_H
#define __FEATHER_H

#ifndef FEATHER 
#error Feather support should not be included.
#endif


#define UnusedAnalog	A3
#define CardSelect	5

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


#endif // __FEATHER_H
