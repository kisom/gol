#ifndef __GOL_H
#define __GOL_H


#include <cstdint>
#include <board.h>

constexpr int		ARRAY_LENGTH = WIDTH * HEIGHT;


struct GameState {
	int		iteration;
	std::uint8_t	array[ARRAY_LENGTH];
};


enum GOLPattern { Random, Beacon, Glider };

void	golInit(GOLPattern pattern);
void	loadFromFile(const char *path);
void	golStep();
void	golDisplay();


#endif // __GOL_H
