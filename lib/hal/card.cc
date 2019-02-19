#include <Arduino.h>
#include <SdFat.h>
#include <SPI.h>
#include <stdint.h>

#include <hal/card.h>


const uint8_t	cardSelect = 10;
static SdFat	card;


bool
cardInit()
{
	if (!card.begin(cardSelect)) {
		return false;
	}
	return true;
}


File
openFile(const char *path, bool write)
{
	if (write) {
		return card.open(path, FILE_WRITE);
	}
	return card.open(path, FILE_READ);
}


bool
cardExists(const char *path)
{
	return card.exists(path);
}


bool
mkdir(const char *path)
{
	return card.mkdir(path);
}


bool
cardRemove(const char *path)
{
	return card.remove(path);
}
