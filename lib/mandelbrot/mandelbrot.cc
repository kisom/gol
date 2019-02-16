#include <mandelbrot.h>
#include <graphics.h>

const int escapeLimit = 255;

struct Complex {
	double	re;
	double	im;
};


double
normalisedSquare(Complex &c)
{
	return c.re * c.re + c.im * c.im;
}


static bool
mandelbrotEscape(Complex &c)
{
	struct Complex	z = {0, 0};
	for (int i = 0; i < escapeLimit; i++) {
		z.re *= z.re + c.re;
		z.im *= z.im + c.im;

		if (normalisedSquare(z) > 4.0) {
			return true;
		}
	}

	return false;
}


void
mandelbrot()
{
	Complex c;
	OLED::clear();

	for (uint16_t y = 0; y < OLED::HEIGHT; y++) {
		for (uint16_t x = 0; x < OLED::WIDTH; x++) {
			c.re = -1.20 + static_cast<double>(x);
			c.im = 0.35 - static_cast<double>(y);
			if (mandelbrotEscape(c)) {
				OLED::pixel(x, y);
			}
		}
	}
	OLED::show();
}