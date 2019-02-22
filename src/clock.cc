#include <string.h>

#include <hal/buttons.h>
#include <hal/graphics.h>
#include <hal/power.h>
#include <hal/rtc.h>
#include <clock.h>


namespace clkScreen {


hal::Button	A(hal::BUTTON_A);
bool		stop = false;


static void
stopButton()
{
	stop = true;
	A.registerCallback(nullptr);
}


void
play()
{
	char	clockBuffer[hal::OLED::MAX_TEXT];
	char	powerBuffer[hal::OLED::MAX_TEXT];

	unsigned long	timeUpdate = 0;
	unsigned long	powerUpdate = 0;

	A.registerCallback(stopButton);

	while (!stop) {
		unsigned long	now = millis();
		A.sample();
		if (timeUpdate < now) {
			hal::OLED::clear();
			hal::rtcFormatTime(clockBuffer);
			hal::OLED::print(0, clockBuffer);
			timeUpdate = millis() + 100;
			hal::OLED::show();
		}

		if (powerUpdate < now) {
			hal::OLED::clear();
			hal::batteryVoltageString(powerBuffer);
			hal::OLED::print(2, powerBuffer);
			powerUpdate = millis() + 60000;
		}
		delay(10);
	}
}


} // namespace clkScreen
