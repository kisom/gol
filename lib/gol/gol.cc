#include <Arduino.h>
#include <SdFat.h>

#include <buttons.h>
#include <card.h>
#include <graphics.h>
#include <gol.h>


static struct GameState	current;
static struct GameState	update;


static inline int 
arrayIndex(int x, int y)
{
	return x + OLED::WIDTH * y;
}


static inline void
pointFromIndex(int idx, int &x, int &y)
{
	x = idx % OLED::WIDTH;
	y = idx / OLED::WIDTH;
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
	if (!cardExists((const char *)"gol/")) {
		mkdir((const char *)"gol/");
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
	nidx = arrayIndex(wrapBack(x, OLED::WIDTH), wrapForward(y, OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 2
	nidx = arrayIndex(x, wrapForward(y, OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 3
	nidx = arrayIndex(wrapForward(x, OLED::WIDTH), wrapForward(y, OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 4
	nidx = arrayIndex(wrapBack(x, OLED::WIDTH), y);
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 5
	nidx = arrayIndex(wrapForward(x, OLED::WIDTH), y);
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 6
	nidx = arrayIndex(wrapBack(x, OLED::WIDTH), wrapBack(y, OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 7
	nidx = arrayIndex(x, wrapBack(y, OLED::HEIGHT));
	if (current.array[nidx]) {
		livingNeighbours++;
	}

	// Neighbour 8
	nidx = arrayIndex(wrapForward(x, OLED::WIDTH), wrapBack(y, OLED::HEIGHT));
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
	int	idx;

	OLED::clear();

	for (size_t row = 0; row < OLED::HEIGHT; row++) {
		for (size_t col = 0; col < OLED::WIDTH; col++) {
			idx = arrayIndex(col, row);
			if (current.array[idx]) {
				OLED::pixel(col, row);	
			}
		}
	}

	OLED::show();
}


void
golStep()
{
	for (size_t row = 0; row < OLED::HEIGHT; row++) {
		for (size_t col = 0; col < OLED::WIDTH; col++) {
			checkNeighbours(col, row);
		}
	}

	for (size_t i = 0; i < ARRAY_LENGTH; i++) {
		current.array[i] = update.array[i];
	}
	current.iteration++;
}


bool
golLoad(const char *path)
{
	File	file = openFile(path, false);
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
		OLED::print(10, 30, (const char *)":(");
		distress();
	}

	return result;

}


bool
golStore(const char *path)
{
	bool	result = false;
	int	i = 0;
	int	pop = 0;

	// ignore errors: if the file doesn't exist, don't worry about
	// the failure to remove.
	cardRemove((char *)path);

	File	file = openFile(path, FILE_WRITE);
	if (!file) {
		goto golStoreFinally;
	}

	for (int row = 0; row < OLED::HEIGHT; row++) {
		for (int col = 0; col < OLED::WIDTH; col++) {
			i = arrayIndex(col, row);
			if (current.array[i]) {
				file.write("*");
				pop++;
			} else {
				file.write(" ");
			}
		}
		file.write("\n");
	}

	file.print("POP: ");
	file.println(pop, DEC);
	file.print("ITER: ");
	file.println(current.iteration, DEC);

golStoreFinally:
	if (file) {
		file.close();
	}
	return result;
}


static unsigned int	golDelay = 100;
static bool		golPlay = true;


void
golButtonA()
{
	if (golDelay > 100) {
		golDelay -= 100;
	}
}


void
golButtonC()
{
	golDelay += 100;
}


void
golButtonB()
{
	static unsigned long	lastPress = 0;

	if ((millis() - lastPress) < 250) {
		Serial.println("resetting game");
		golInit(Random);
		golStore("gol/initial.txt");
		golDisplay();
	}

	lastPress = millis();
	Serial.print("last press: ");
	Serial.println(lastPress);

	golPlay = !golPlay;
	if (!golPlay) {
		golStore("gol/current.txt");
	}
}


void
playGameOfLife()
{
	unsigned long	nextUpdate = 0;
	Button		buttonA(9);
	Button		buttonB(6);
	Button		buttonC(5);

	buttonA.registerCallback(golButtonA);
	buttonB.registerCallback(golButtonB);
	buttonC.registerCallback(golButtonC);

	if (cardExists("gol/current.txt")) {
		golLoad("gol/current.txt");
	} else {
		golInit(Random);
		golStore("gol/initial.txt");
	}
	golDisplay();

	while (true) {
		buttonA.sample();
		buttonB.sample();
		buttonC.sample();
		if (golPlay && (millis() > nextUpdate)) {
			golStep();
			golDisplay();
			if ((current.iteration % 10) == 0) {
				golStore("gol/current.txt");
			}
			nextUpdate = millis() + golDelay;
		}
	}
}
