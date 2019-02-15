#ifndef __CARD_H
#define __CARD_H


#include <Arduino.h>
#include <SdFat.h>
#include <SPI.h>


bool	cardInit();
File	openFile(const char *path, bool write);
bool	cardExists(const char *path);
bool	cardRemove(const char *path);
bool	mkdir(const char *path);


#endif // __CARD_H
