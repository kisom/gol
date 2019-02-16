#include <Arduino.h>
#include <audio.h>


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
