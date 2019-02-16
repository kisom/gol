BOARD :=	feather_m4
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin
SOURCES :=					\
		lib/audio/audio.h		\
		lib/audio/audio.cc		\
		lib/buttons/buttons.h		\
		lib/buttons/buttons.cc		\
		lib/card/card.h			\
		lib/card/card.cc		\
		lib/gol/gol.h			\
		lib/gol/gol.cc			\
		lib/graphics/graphics.h		\
		lib/graphics/graphics.cc	\
		lib/mandelbrot/mandelbrot.h	\
		lib/mandelbrot/mandelbrot.cc	\
		lib/power/power.h		\
		lib/power/power.cc		\
		lib/random/random.h		\
		lib/random/random.cc		\
		lib/rtc/rtc.h			\
		lib/rtc/rtc.cc			\
		lib/util/util.h			\
		lib/util/util.cc		\
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
	$(PIO) -t upload && sleep 0.2 && $(PIO) -t monitor

.PHONY: clean
clean:
	$(PIO) -t clean
