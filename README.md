CBN
===

This started out as a Game of Life played on a small ARM board with an
I2C OLED. I've decided to turn it into a exploration of computing in
the spirit of the Computational Beauty of Nature. This uses a couple of
libraries and the Arduino framework in PlatformIO because it isn't an
exercise in embedded programming necessarily.


Board support
-------------

The minimum hardware I'd like for my explorations are

* an OLED to draw things on
* a few buttons to control things
* an RTC to keep track of the time
* an SD card for data storage
* some kind of audio output to make music

I've settled on the Adafruit Feathers. I have the Feather M4 for the
main board, with the Adalogger and OLED FeatherWings. I wanted to add
a GPS, but it doesn't have an SD card (and then I'd have two modules
with coin cells) and the music maker, but it uses the same pins as the
display's buttons. I've found 3 modules is a tenable size; I'm not sure
about the others.

The `lib` directory contains small libraries for utility functions
and the hardware abstraction layer.

TODO: write up the HAL
TODO: write up utilities
TODO: move hardware support to a HAL library.

## Explorations

#### Game of Life

This is a simple implementation of Conway's Game of Life. It could use
some improvements, like a bit buffer instead of a byte buffer. If there
is a game in progress, it is resumed; otherwise, the world is generated
randomly. The initial game state (and regular updates) are stored on the
SD card under `gol/initial.txt` and `gol/current.txt` - these are human
readable, too. The controls are

* A: speed up the simulation by 100ms between steps (minimum of 100 ms
  between steps) - e.g. if there are 1000ms between steps, pressing this
  twice gives 1000ms - 100ms - 100ms = 800ms between steps.
* B: pause the simulation, saving the game state. Double pressing
  the button within 250 ms will cause the simulation to reset to a new
  random game state.
* C: slow down the simulation by 100ms between steps.
