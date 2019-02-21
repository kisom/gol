#include <Arduino.h>
#include <SdFat.h>

#include <hal/buttons.h>
#include <hal/card.h>
#include <hal/graphics.h>
#include <hal/power.h>
#include <gol.h>


namespace gol {

constexpr int		ARRAY_LENGTH = hal::OLED::HEIGHT * hal::OLED::WIDTH;

struct GameState {
	int	iteration;
	int	population;
	uint8_t	array[ARRAY_LENGTH];
};

static struct GameState	current;
static struct GameState	update;
static int		longestIteration;
static unsigned int	golDelay = 100;
static bool		golPlay = true;


enum GOLPattern { Random, Beacon, Glider };


static inline int 
arrayIndex(int x, int y)
{
	return x + hal::OLED::WIDTH * y;
}


static inline void
pointFromIndex(int idx, int &x, int &y)
{
	x = idx % hal::OLED::WIDTH;
	y = idx / hal::OLED::WIDTH;
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


static void
patternRandom()
{
	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		current.array[i] = random(1, 3) - 1;
	}
}


static void
loadStats()
{
	char	ch;

	longestIteration = 0;
	if (!hal::card::exists("gol/stats.txt")) {
		return;
	}

	File	stats = hal::card::openFile("gol/stats.txt", false);
	if (!stats) {
		hal::OLED::print(0, "SD error");
		hal::distress();
	}

	while (stats.available()) {
		ch = stats.read();
		if (ch == '\n') {
			break;
		}

		longestIteration *= 10;
		longestIteration += (int)ch & 0xFF;
	}

	stats.close();
}


static bool
writeStats()
{
	File	stats = hal::card::openFile("gol/stats.txt", true);

	if (!stats) {
		return false;
	}

	stats.println(longestIteration);
	stats.close();
	return true;
}


static void
init(GOLPattern pattern)
{
	if (!hal::card::exists((const char *)"gol/")) {
		hal::card::mkdir((const char *)"gol/");
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

	loadStats();	
}


static inline int 
wrapBack(int v, int border)
{
	if (v == 0) {
		v = border;
	}
	v--;

	return v;
}


static inline int 
wrapForward(int v, int border)
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
checkNeighbours(int x, int y)
{
	// Neighbours:
	// 123
	// 4*5
	// 678
	
	uint8_t	livingNeighbours = 0;
	int	idx = arrayIndex(x, y);
	int	nidx; // Neighbour index.
	
	// Neighbour 1
	nidx = arrayIndex(wrapBack(x, hal::OLED::WIDTH), wrapForward(y, hal::OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 2
	nidx = arrayIndex(x, wrapForward(y, hal::OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 3
	nidx = arrayIndex(wrapForward(x, hal::OLED::WIDTH), wrapForward(y, hal::OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 4
	nidx = arrayIndex(wrapBack(x, hal::OLED::WIDTH), y);
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 5
	nidx = arrayIndex(wrapForward(x, hal::OLED::WIDTH), y);
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 6
	nidx = arrayIndex(wrapBack(x, hal::OLED::WIDTH), wrapBack(y, hal::OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 7
	nidx = arrayIndex(x, wrapBack(y, hal::OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 8
	nidx = arrayIndex(wrapForward(x, hal::OLED::WIDTH), wrapBack(y, hal::OLED::HEIGHT));
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


static void
display()
{
	int	idx;

	hal::OLED::clear();

	for (size_t row = 0; row < hal::OLED::HEIGHT; row++) {
		for (size_t col = 0; col < hal::OLED::WIDTH; col++) {
			idx = arrayIndex(col, row);
			if (current.array[idx]) {
				hal::OLED::pixel(col, row);	
			}
		}
	}

	hal::OLED::show();
}


static void
updateGame()
{
	current.population = 0;
	for (size_t row = 0; row < hal::OLED::HEIGHT; row++) {
		for (size_t col = 0; col < hal::OLED::WIDTH; col++) {
			checkNeighbours(col, row);
		}
	}

	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		current.array[i] = update.array[i];
		if (current.array[i]) {
			current.population++;
		}
	}
	current.iteration++;
}


static bool
load(const char *path)
{
	File	file = hal::card::openFile(path, false);
	bool	result = false;
	int	i = 0;
	int	ch = 0;

	if (!file) {
		goto golLoadFinally;
	}

	while (i < ARRAY_LENGTH && file.available()) {
		ch = file.read();

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

	result = true;

golLoadFinally:
	if (file) {
		file.close();
	}

	if (!result) {
		hal::OLED::print(0, "SD READ FAIL");
		hal::distress();
	}

	return result;

}


static uint8_t
store(const char *path)
{
	uint8_t	result = 1;
	int	i = 0;
	int	pop = 0;

	// ignore errors: if the file doesn't exist, don't worry about
	// the failure to remove.
	hal::card::remove((char *)path);

	File	file = hal::card::openFile(path, FILE_WRITE);
	if (!file) {
		result = file.getError();
		goto golStoreFinally;
	}

	for (int row = 0; row < hal::OLED::HEIGHT; row++) {
		for (int col = 0; col < hal::OLED::WIDTH; col++) {
			i = arrayIndex(col, row);
			if (current.array[i]) {
				file.write("*");
				pop++;
			} else {
				file.write(" ");
			}
		}
		file.write("\n");
		file.flush(); // try to avoid a power spike from writing to the SD card.
	}

	file.print("POP: ");
	file.println(pop, DEC);
	file.print("ITER: ");
	file.println(current.iteration, DEC);
	result = 0;

	writeStats();

golStoreFinally:
	if (file) {
		file.close();
	}
	return result;
}


static void
golButtonA()
{
	if (golDelay > 100) {
		golDelay -= 100;
	}
}


static void
golButtonC()
{
	golDelay += 100;
}


static void
golButtonB()
{
	static unsigned long	lastPress = 0;

	if ((millis() - lastPress) < 500) {
		init(Random);
		store("gol/initial.txt");
		display();
	}

	lastPress = millis();

	golPlay = !golPlay;
	if (!golPlay) {
		store("gol/current.txt");
	}
}


static void
step(unsigned long &nextUpdate, hal::Button &a, hal::Button &b, hal::Button &c)
{
	static int	lastPopulation;
	static uint8_t	stagnation = 0;
	uint8_t		sdResult = 0;

	a.sample();
	b.sample();
	c.sample();
	if (golPlay && (millis() > nextUpdate)) {
		lastPopulation = current.population;
		updateGame();
		display();
		if ((current.iteration % 100) == 0) {
			if ((sdResult = store("gol/current.txt")) != 0) {
				char	buf[4];
				hal::OLED::clear();
				hal::OLED::print(0, "SD error");
				snprintf(buf, 4, "%d", sdResult);
				hal::OLED::print(1, buf);
				hal::distress();
			}
		}

		// detect stagnation.
		if (current.population == lastPopulation) {
			stagnation++;
			if (stagnation > 50) {
				char	battery[8];
				hal::OLED::clearLines();
				hal::OLED::print(0, "STAGNANT POP");
				hal::batteryVoltageString(battery);
				hal::OLED::print(1, battery);
				delay(1500);
				hal::OLED::clearLines();
				init(Random);
				lastPopulation = 0;
				stagnation = 0;
			}
		}
		else {
			stagnation = 0;
		}
	
		nextUpdate = millis() + golDelay;
	}
}


static void
splash()
{
	hal::OLED::clear();
	hal::OLED::print(1, "  GAME ");
	delay(500);
	hal::OLED::print(1, "  GAME OF ");
	delay(500);
	hal::OLED::print(1, "  GAME OF LIFE");
	delay(1000);
}


void
play()
{
	play(false);
}


void
play(bool reset)
{
	unsigned long	nextUpdate = 0;
	hal::Button	buttonA(hal::BUTTON_A);
	hal::Button	buttonB(hal::BUTTON_B);
	hal::Button	buttonC(hal::BUTTON_C);

	buttonA.registerCallback(golButtonA);
	buttonB.registerCallback(golButtonB);
	buttonC.registerCallback(golButtonC);

	splash();
	if (!reset && hal::card::exists("gol/current.txt")) {
		load("gol/current.txt");
	} else {
		init(Random);
		store("gol/initial.txt");
	}
	display();

	while (true) {
		step(nextUpdate, buttonA, buttonB, buttonC);
	}
}

}
