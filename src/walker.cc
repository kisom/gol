#include <Arduino.h>

#include <hal/buttons.h>
#include <hal/graphics.h>
#include <noise.h>
#include <walker.h>


namespace walker {


noise::NoiseGenerator	perlinX;
noise::NoiseGenerator	perlinY;
static uint16_t		x = 64;
static uint16_t		y = 16;
static double		t = 0.0;
static uint16_t		kx = 1;
static uint16_t		ky = 1;
static const double	dt = 0.001;
static bool		active = true;


void
init()
{
	x = 64;
	y = 16;
	t = 0.0;
	active = true;
	perlinX.randomise();
	perlinY.randomise();
}


static uint16_t
noiseStep(uint16_t v, uint16_t max, uint16_t &k, double dv)
{
	if (dv < 0.3) {
		if (v > 0) {
			v -= k;
		}
		else {
			k = -k;
		}
	}
	else if (v > 0.6) {
		if (v < max) {
			v += k;
		}
		else {
			k = -k;
		}
	}

	return v;
}


void
step()
{
	hal::OLED::clear();
	hal::OLED::pixel(x, y);

	t += dt;
	double	dx = perlinX.sample(t, t, t);
	double	dy = perlinY.sample(t, t, t);
	Serial.print("STEP: ");
	Serial.print(dx);
	Serial.print(" - ");
	Serial.println(dy);

	x = noiseStep(x, hal::OLED::WIDTH, kx, dx);
	y = noiseStep(y, hal::OLED::HEIGHT, ky, dy);

	hal::OLED::circle(x, y, 3, false);
	hal::OLED::show();
}


static void
toggleGame()
{
	Serial.println("reset walker");
	active = !active;
}


void
play()
{
	hal::Button	buttonC(hal::BUTTON_C);
	hal::Button	buttonB(hal::BUTTON_B);
	unsigned long	next = millis() + 100;
	init();

	// buttonB.registerCallback(toggleGame);
	buttonC.registerCallback(init);

	while (true) {
		buttonC.sample();
		buttonB.sample();
		if (active && (millis() < next)) {
			step();
			next = millis() + 100;
		}
		delay(10);
	}
}


} // namespace walker
