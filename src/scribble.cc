#include <Arduino.h>
#include <Streaming.h>

#include <hal/buttons.h>
#include <hal/graphics.h>
#include <hal/power.h>
#include <scribble.h>


namespace scribble {


struct hal::Point	previous;
struct hal::Point	current;
uint16_t		time, lifetime;
bool			active = false;


static void
init()
{
	char	buf[9];

	current.x = random(hal::OLED::WIDTH);
	current.y = random(hal::OLED::HEIGHT);
	time = 0;
	lifetime = random(0, 128);
	active = true;
	hal::OLED::clear();

	hal::OLED::print(1, "SCRIBBLE");
	hal::batteryVoltageString(buf);
	hal::OLED::print(2, buf);
	delay(1000);
	hal::OLED::clear();
}


static void
step()
{
	previous.x = current.x;
	previous.y = current.y;
	time++;

	uint8_t	op = random(2);
	if (op == 0) {
		current.x = random(hal::OLED::WIDTH);
		current.y = random(hal::OLED::HEIGHT);
		hal::OLED::line(previous.x, previous.y,
				current.x, current.y);
	}
	else {
		uint8_t	r = random(2) + 1;
		bool fill = random(2);
		hal::OLED::circle(current.x, current.y, r, fill);
	}

	hal::OLED::show();
}


static void
splash()
{
	char	title[9] = "SCRIBBLE";
	char	buf[9];

	hal::OLED::clear();
	for (uint8_t i = 0; i < 8; i++) {
		buf[i] = title[i];
		buf[i+1] = 0;
		hal::OLED::print(1, buf);
		hal::OLED::show();
		delay(100);
	}

	for (uint8_t i = 0; i < 2; i++) {
		hal::OLED::iprint(1, title);
		delay(250);
		hal::OLED::print(1, title);
		delay(250);
	}
}


void
play()
{
	hal::Button	B(hal::BUTTON_B);
	unsigned long	resetAfter = millis() + 5000;

	splash();
	init();
	B.registerCallback(init);

	while (true) {
		B.sample();
		if (time > lifetime) {
			active = false;
		}

		if (resetAfter < millis()) {
			resetAfter = millis() + 5000;
			init();
			continue;
		}

		if (active) {
			step();
			resetAfter = millis() + 5000;
		}

		delay(10);
	}
}


} // namespace scribble
