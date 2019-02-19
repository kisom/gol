#include <Arduino.h>
#include <hal/audio.h>


namespace hal {
void
audioSetup()
{
	pinMode(SpeakerPin, OUTPUT);
}


void
audioTone(int frequency)
{
	tone(SpeakerPin, frequency);
}


void
audioMute()
{
	noTone(SpeakerPin);
}


} // namespace hal