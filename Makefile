BOARD :=	feather
FIRMWARE :=	.pioenvs/$(BOARD)/firmware.bin
SOURCES :=	src/main.cc		\
		src/gol.cc		\
		src/redboard.cc		\
		src/feather.cc		\
		include/feather.h	\
		include/redboard.h	\
		include/gol.h

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
