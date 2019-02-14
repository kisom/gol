#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include <card.h>


Sd2Card		card;
SdVolume	volume;


bool
cardInit(int cs)
{
	if (!card.init(cs, SPI_FULL_SPEED)) {
		return false;
	}

	if (!volume.init(card)) {
		return false;
	}
}


File
openFile(const char *path, bool write)
{

}

