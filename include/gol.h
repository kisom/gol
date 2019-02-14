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
void	golStep();
void	golDisplay();
// bool	golLoad(const char *path);
// bool	golStore(const char *path);


#endif // __GOL_H
