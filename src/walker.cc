#include <Arduino.h>
#include <Streaming.h>

#include <hal/buttons.h>
#include <hal/graphics.h>
#include <util/util.h>
#include <noise.h>
#include <walker.h>


namespace walker {


static uint16_t		x = 64;
static uint16_t		y = 16;
static bool		active = true;


void
init()
{
	x = 64;
	y = 16;
	active = true;
}


void
step()
{
	hal::OLED::clear();
	hal::OLED::pixel(x, y);

	int16_t dx = random(-1, 2);
	int16_t dy = random(-1, 2);

	x = dclamp_u16(x, dx, hal::OLED::WIDTH);
	y = dclamp_u16(y, dy, hal::OLED::HEIGHT);

	hal::OLED::circle(x, y, 3, false);
	hal::OLED::show();
}


static void
toggleGame()
{
	Serial.println("toggle walker");
	bool oldActive = active;
	active = !active;
	Serial << "from " << oldActive << " to " << active << endl;
}


void
play()
{
	hal::Button	buttonC(hal::BUTTON_C);
	hal::Button	buttonB(hal::BUTTON_B);
	unsigned long	next = millis() + 50;
	init();

	buttonB.registerCallback(toggleGame);
	buttonC.registerCallback(init);

	while (true) {
		buttonC.sample();
		buttonB.sample();
		if (active && (next < millis())) {
			step();
			next = millis() + 50;
		}
		delay(10);
	}
}


} // namespace walker
