#include <Arduino.h>

#include <hal/buttons.h>
#include <hal/graphics.h>
#include <noise/noise.h>
#include <walker.h>


namespace walker {


noise::NoiseGenerator	perlin;
static uint16_t		x = 64;
static uint16_t		y = 16;
static double		xt = 0.0;
static double		yt = 0.0;
static const double	dt = 0.001;
static bool		active = true;


void
init()
{
	x = 64;
	y = 16;
	t = 0.0;
}


static uint16_t
noiseStep(uint16_t v, uint16_t max, double dv)
{
	if (dv < 0.1) {
		if (v > 0) {
			v--;
		}
	}
	else if (v > 0.1) {
		if (v < max) {
			v++;
		}
	}

	return v;
}


void
step()
{
	hal::OLED::clear();
	hal::OLED::pixel(x, y);

	xt += dt;
	yt += dt;
	double	dx = noise.step(xt, xt, xt);
	double	dy = noise.step(yt, yt, yt);

	x = noiseStep(x, hal::OLED::WIDTH, dx);
	y = noiseStep(y, hal::OLED::HEIGHT, dy);

	hal::OLED::circle(x, y, 3, false);
	hal::OLED::show();
}


static void
toggleGame()
{
	active = !active;
}


void
play()
{
	hal::Button	buttonB(hal::BUTTON_B);
	init();

	buttonB.registerCallback(toggleGame);

	while (true) {
		if (active) {
			step();
		}
		delay(100);
	}
}


} // namespace walker
