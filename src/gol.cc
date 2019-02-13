#include <Arduino.h>
#include <Streaming.h>
#include <gol.h>


static struct GameState	current;
static struct GameState	update;


void
initGame()
{
	current.iteration = 0;
	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		current.array[i] = 0;
	}
}


void
display()
{
	Serial << "ITER: " << current.iteration << endl;
	for (size_t row = 0; row < HEIGHT; row++) {
		for (size_t col = 0; col < WIDTH; col++) {
			if (current.array[col + row * HEIGHT]) {
				Serial << "*";
			} else {
				Serial << " ";
			}
		}
		Serial << endl;
	}
}
