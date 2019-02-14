#include <Arduino.h>
#include <SD.h>
#include <Streaming.h>

#include <board.h>
#include <gol.h>


static struct GameState	current;
static struct GameState	update;


static inline size_t
arrayIndex(std::size_t x, std::size_t y)
{
	return x + WIDTH * y;
}


static inline void
pointFromIndex(std::size_t idx, std::size_t &x, std::size_t &y)
{
	x = idx % WIDTH;
	y = idx / WIDTH;
}


static void
patternBeacon()
{
	current.array[arrayIndex(1, 1)] = 1;
	current.array[arrayIndex(2, 1)] = 1;
	current.array[arrayIndex(1, 2)] = 1;
	current.array[arrayIndex(2, 2)] = 1;
	current.array[arrayIndex(3, 3)] = 1;
	current.array[arrayIndex(4, 3)] = 1;
	current.array[arrayIndex(3, 4)] = 1;
	current.array[arrayIndex(4, 4)] = 1;
}


static void
patternGlider()
{
	current.array[arrayIndex(0, 0)] = 1;
	current.array[arrayIndex(1, 0)] = 1;
	current.array[arrayIndex(2, 0)] = 1;
	current.array[arrayIndex(2, 1)] = 1;
	current.array[arrayIndex(1, 2)] = 1;
}


void
patternRandom()
{
	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		current.array[i] = random(1, 3) - 1;
	}
}

void
golInit(GOLPattern pattern)
{
	clearDisplay();

	if (!SD.exists((char *)"gol/")) {
		SD.mkdir((char *)"gol/");
	}

	current.iteration = 0;
	switch (pattern) {
	case Random:
		patternRandom();
		break;
	case Beacon:
		patternBeacon();
		break;
	case Glider:
		patternGlider();
		break;
	default:
		patternRandom();
	}
}


static inline size_t 
wrapBack(std::size_t v, std::size_t border)
{
	if (v == 0) {
		v = border;
	}
	v--;

	return v;
}

static inline size_t 
wrapForward(std::size_t v, std::size_t border)
{
	if (v == (border - 1)) {
		v = 0;
	}
	else {
		v++;
	}

	return v;
}

static void
checkNeighbours(std::size_t x, std::size_t y)
{
	// Neighbours:
	// 123
	// 4*5
	// 678
	
	std::uint8_t	livingNeighbours = 0;
	std::size_t	idx = arrayIndex(x, y);
	std::size_t	nidx; // Neighbour index.
	
	// Neighbour 1
	nidx = arrayIndex(wrapBack(x, WIDTH), wrapForward(y, HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 2
	nidx = arrayIndex(x, wrapForward(y, HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 3
	nidx = arrayIndex(wrapForward(x, WIDTH), wrapForward(y, HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 4
	nidx = arrayIndex(wrapBack(x, WIDTH), y);
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 5
	nidx = arrayIndex(wrapForward(x, WIDTH), y);
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 6
	nidx = arrayIndex(wrapBack(x, WIDTH), wrapBack(y, HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 7
	nidx = arrayIndex(x, wrapBack(y, HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 8
	nidx = arrayIndex(wrapForward(x, WIDTH), wrapBack(y, HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	update.array[idx] = 0;
	if (!current.array[idx]) {
		if (livingNeighbours == 3) {
			update.array[idx] = 1;
		}
	}
	else if ((livingNeighbours == 2) || (livingNeighbours == 3)) {
		update.array[idx] = 1;
	}
}


void
golDisplay()
{
	std::size_t	idx;

	clearDisplay();

	for (size_t row = 0; row < HEIGHT; row++) {
		for (size_t col = 0; col < WIDTH; col++) {
			idx = arrayIndex(col, row);
			if (current.array[idx]) {
				drawPixel(col, row);	
			}
		}
	}

	updateDisplay();
}


void
golStep()
{
	for (size_t row = 0; row < HEIGHT; row++) {
		for (size_t col = 0; col < WIDTH; col++) {
			checkNeighbours(col, row);
		}
	}

	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		current.array[i] = update.array[i];
	}
	current.iteration++;
}


/*
bool
golLoad(const char *path)
{
	File	file = SD.open(path);
	bool	result = false;
	int	i = 0;
	int	ch = 0;
	
	if (!file) {
		goto golLoadFinally;
	}

	while (i < ARRAY_LENGTH) {
		file >> ch;

		switch (ch) {
		case -1:
			goto golLoadFinally;
			break;
		case 0x20:
			current.array[i] = 0;
			break;
		case 0x2A:
			current.array[i] = 1;
			break;
		default:
			continue;
		}

		i++;
	}

golLoadFinally:
	if (file) {
		file.close();
	}

	return result;

}


bool
golStore(const char *path)
{
	File	file = SD.open(path, FILE_WRITE);
	bool	result = false;
	int	i = 0;

	if (!file) {
		goto golStoreFinally;
	}

	for (int row = 0; row < HEIGHT; row++) {
		for (int col = 0; col < WIDTH; col++) {
			i = arrayIndex(col, row);
			if (current.array[i]) {
				file << "*";
			} else {
				file << " ";
			}
		}
		file << endl;
	}

golStoreFinally:
	if (file) {
		file.close();
	}
	return result;
}

*/
