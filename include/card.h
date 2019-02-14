#ifndef __CARD_H
#define __CARD_H


#include <Arduino.h>
#include <SD.h>
#include <SPI.h>


bool	cardInit(int cs);
File	openFile(const char *path, bool write);


#endif // __CARD_H
