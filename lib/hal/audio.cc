#include <Arduino.h>
#include <hal/audio.h>


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
