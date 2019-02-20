#ifndef __GRAPHICS_H
#define __GRAPHICS_H


#include <stdint.h>


namespace hal {


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

static const int	HEIGHT = 32;
static const int	WIDTH  = 128;
static const int	MAX_TEXT = 20;

void	setup();
void	clear();
void	pixel(uint16_t x, uint16_t y);
void	clearPixel(uint16_t x, uint16_t y);
void	circle(uint16_t x, uint16_t y, uint16_t r, bool fill);
void	show();

// Text display routines.
void	clearLines();
void	print(uint8_t line, const char *text);
void	iprint(uint8_t line, const char *text);
void	scrollForward(const char *text, bool inverse);
void	scrollBackward(const char *text, bool inverse);


} // namespace OLED
} // namespace hal
#endif // __GRAPHICS_H