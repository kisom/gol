#ifndef __GOL_H
#define __GOL_H


#include <cstddef>
#include <cstdint>

static const std::size_t	WIDTH = 128;
static const std::size_t	HEIGHT = 64;
constexpr std::size_t		ARRAY_LENGTH = WIDTH * HEIGHT;


struct GameState {
	std::size_t	iteration;
	std::uint8_t	array[ARRAY_LENGTH];
};


void	initGame();
void	loadFromFile(const char *path);
void	step();
void	display();


#endif // __GOL_H
