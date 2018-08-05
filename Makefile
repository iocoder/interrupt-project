MCU=atmega32
CFLAGS=-g -Os -mmcu=$(MCU)
OFLAGS=-j .text -j .data -O ihex
CC=avr-gcc
OBJCOPY=avr-objcopy

SRC=irq.c led.c btn.c tmr.c main.c
HDR=irq.h led.h btn.h tmr.h
PRG=program
EXE=$(PRG).exe
HEX=$(PRG).hex

all: $(HEX)

$(HEX): $(EXE)
	$(OBJCOPY) $(OFLAGS) $< $@

$(EXE): $(SRC) $(HDR)
	$(CC) $(CFLAGS) -o $@ $(SRC)

clean:
	rm -rf $(EXE) $(HEX)
