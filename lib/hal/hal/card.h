#ifndef __CARD_H
#define __CARD_H


#include <Arduino.h>
#include <SdFat.h>
#include <SPI.h>


namespace hal {
namespace card {

bool	init();
File	openFile(const char *path, bool write);
bool	exists(const char *path);
bool	remove(const char *path);
bool	mkdir(const char *path);


} // namespace card
} // namespace hal
#endif // __CARD_H
