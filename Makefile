BOARD :=	feather_m0
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin
SOURCES :=					\
		lib/buttons/buttons.cc		\
		lib/buttons/buttons.h		\
		lib/card/card.cc		\
		lib/card/card.h			\
		lib/gol/gol.cc			\
		lib/gol/gol.h			\
		lib/graphics/graphics.cc	\
		lib/graphics/graphics.h		\
		lib/power/power.cc		\
		lib/power/power.h		\
		lib/rtc/rtc.cc			\
		lib/rtc/rtc.h			\
		lib/util/util.cc		\
		lib/util/util.h			\
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
