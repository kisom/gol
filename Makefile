BOARD :=	feather_m0
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin
SOURCES :=	include/avr.h		\
		include/buttons.h	\
		include/card.h		\
		include/gol.h		\
		include/graphics.h	\
		include/power.h		\
		include/rtc.cc		\
		include/util.h		\
		src/buttons.cc		\
		src/card.cc		\
		src/gol.cc		\
		src/graphics.cc		\
		src/main.cc		\
		src/power.cc		\
		src/rtc.cc		\
		src/util.cc

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
