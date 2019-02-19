#ifndef __GRAPHICS_H
#define __GRAPHICS_H


#include <stdint.h>


void	distress();

struct Point {
	uint16_t	x;
	uint16_t	y;
};


// euclidist computes the Euclidean distance between two points.
uint16_t	delta(uint16_t a, uint16_t b);
double		euclidist(Point &a, Point &b);

void		neoPixel(uint8_t r, uint8_t g, uint8_t b);
void		neoPixelBrightness(uint8_t brightness);


namespace OLED {

static const int HEIGHT = 32;
static const int WIDTH  = 128;

void	setup();
void	clear();
void	pixel(uint16_t x, uint16_t y);
void	clearPixel(uint16_t x, uint16_t y);
void	circle(uint16_t x, uint16_t y, uint16_t r, bool fill);
void	print(uint8_t line, const char *text);
void	print(uint16_t x, uint16_t y, const char *text);
void	print(uint16_t x, uint16_t y, double value, int precision);
void	show();

} // namespace OLED

#endif // __GRAPHICS_H
