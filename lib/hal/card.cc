#include <Arduino.h>
#include <SdFat.h>
#include <SPI.h>
#include <stdint.h>

#include <hal/card.h>


namespace hal {
namespace card {

const uint8_t	cardSelect = 10;
static SdFat	sdcard;


bool
init()
{
	if (!sdcard.begin(cardSelect)) {
		return false;
	}
	return true;
}


File
openFile(const char *path, bool write)
{
	if (write) {
		return sdcard.open(path, FILE_WRITE);
	}
	return sdcard.open(path, FILE_READ);
}


bool
exists(const char *path)
{
	return sdcard.exists(path);
}


bool
mkdir(const char *path)
{
	return sdcard.mkdir(path);
}


bool
remove(const char *path)
{
	return sdcard.remove(path);
}


} // namespace card
} // namespace hal