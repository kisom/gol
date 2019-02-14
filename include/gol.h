#ifndef __GOL_H
#define __GOL_H


#include <cstdint>
#include <board.h>

constexpr int		ARRAY_LENGTH = WIDTH * HEIGHT;


struct GameState {
	int		iteration;
	std::uint8_t	array[ARRAY_LENGTH];
};


enum Pattern { Random, Beacon, Glider };

void	initGame(Pattern pattern);
void	loadFromFile(const char *path);
void	step();
void	display();


#endif // __GOL_H
