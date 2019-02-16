#ifndef __GOL_H
#define __GOL_H


#include <stdint.h>
#include <graphics.h>

constexpr int		ARRAY_LENGTH = OLED::HEIGHT * OLED::WIDTH;


struct GameState {
	int	iteration;
	int	population;
	uint8_t	array[ARRAY_LENGTH];
};


enum GOLPattern { Random, Beacon, Glider };

void	golInit(GOLPattern pattern);
void	golStep();
void	golDisplay();
bool	golLoad(const char *path);
bool	golStore(const char *path);

// playGameOfLife enters the game loop.
void	playGameOfLife();


#endif // __GOL_H
