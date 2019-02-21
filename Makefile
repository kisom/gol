BOARD :=	feather_m4
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin
SOURCES :=					\
		lib/hal/hal/audio.h		\
		lib/hal/audio.cc		\
		lib/hal/hal/buttons.h		\
		lib/hal/buttons.cc		\
		lib/hal/hal/card.h		\
		lib/hal/card.cc			\
		lib/hal/hal/graphics.h		\
		lib/hal/graphics.cc		\
		lib/hal/hal/power.h		\
		lib/hal/power.cc		\
		lib/hal/hal/random.h		\
		lib/hal/random.cc		\
		lib/hal/hal/rtc.h		\
		lib/hal/rtc.cc			\
		lib/hal/util/util.h		\
		lib/hal/util/util.cc		\
		lib/noise/noise.h		\
		lib/noise/noise.cc		\
		include/gol.h			\
		include/mandelbrot.h		\
		include/scribble.h		\
		include/walker.h		\
		src/gol.cc			\
		src/mandelbrot.cc		\
		src/scribble.cc			\
		src/walker.cc			\
		src/main.cc

PIO :=	pio run -e $(BOARD)

$(FIRMWARE): $(SOURCES)
	$(PIO)

PHONY: all
all: $(FIRMWARE)

.PHONY: upload
upload: $(FIRMWARE)
	$(PIO) -t upload

.PHONY: monitor
monitor:
	$(PIO) -t monitor

.PHONY: deploy
deploy: $(FIRMWARE)
	$(PIO) -t upload && sleep 0.5 && $(PIO) -t monitor

.PHONY: clean
clean:
	$(PIO) -t clean

.PHONY:
cloc:
	cloc include lib src
