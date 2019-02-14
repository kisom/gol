CBN
===

This started out as a Game of Life played on a small ARM board with an
I2C OLED. I've decided to turn it into a exploration of computing in
the spirit of the Computational Beauty of Nature. This uses a couple of
libraries and the Arduino framework in PlatformIO because it isn't an
exercise in embedded programming necessarily.

Note that while this (currently) supports the Sparkfun Redboard Turbo and
MicroOLED breakout, it won't in the future as this setup doesn't have any
inputs.


Board support
-------------

The minimum hardware I'd like for my explorations are

* an OLED to draw things on
* a few buttons to control things
* an RTC to keep track of the time
* an SD card for data storage
* some kind of audio output to make music

The board support packages are provided by including `board.h` and should
provide the following:

### Graphics routines

* `setupDisplay()` to initialise the display.
* `clearDisplay()` should erase the contents of the screen.
* `drawPixel(int x, int y)` should allow you to put a pixel on the
  screen. Right now, the displays that I'm using are monochrome, so
  there's that.
* `clearPixel(int x, int y)` should allow you to clear a pixel on
  the screen.
* `updateDisplay()` should refresh the screen buffer.

TODO (with tentative APIs):
* `circle(int x, int y, int r)`
* `rect(int x, int y, int w, int l)`

### SD card (TODO)

* `readFile(const char *path, uint8_t *buf, unsigned len)` should
  read a file from the SD card.
* `writeFile(const char *path, uint8_t *buf, unsigned len)` should
  write a file to the SD card.

### Other features

* `UnusedAnalog` is used at the beginning to seed the PRNG. It's a sort of
  hacky, non-cryptographically safe method: a number of `analogRead`s
  are done on the unused analog port, and the four LSBs are used to build
  an unsigned long seed value.

## Explorations

#### Game of Life

This is a simple implementation of Conway's Game of Life. It could use
some improvements, like a bit buffer instead of a byte buffer. The
main functions are

* `golInit(GOLPattern pattern)` where the patterns are

  * `Random` to randomly generate a universe
  * `Beacon` generates an oscillating beacon, which was used for testing
  * `Glider` flies a little glider across the screen

* `step
