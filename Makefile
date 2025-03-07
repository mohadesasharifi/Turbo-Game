# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   12 Sep 2010
# Descr:  Makefile for game

# Definitions.
CC = avr-gcc
CFLAGS = -mmcu=atmega32u2 -Os -Wall -Wstrict-prototypes -Wextra -g -I. -I../../utils -I../../fonts -I../../drivers -I../../drivers/avr
OBJCOPY = avr-objcopy
SIZE = avr-size
DEL = rm


# Default target.
all: game.out


# Compile: create object files from C source files.
game.o: game.c turbo.h game.h blueLed.h buttonControl.h turboDisplay.h ../../utils/task.h demo.h 
	$(CC) -c $(CFLAGS) $< -o $@

# Compile: create object files from C source files.
turbo.o: turbo.c ../../utils/tinygl.h ../../utils/task.h game.h turbo.h buttonControl.h demo.h
	$(CC) -c $(CFLAGS) $< -o $@

demo.o: demo.c ../../utils/tinygl.h ../../fonts/font3x5_1.h ../../utils/font.h demo.h game.h
	$(CC) -c $(CFLAGS) $< -o $@

buttonControl.o: buttonControl.c ../../drivers/navswitch.h ../../drivers/avr/timer.h buttonControl.h ../../utils/task.h blueLed.h turbo.h game.h turboFood.h
	$(CC) -c $(CFLAGS) $< -o $@

turboDisplay.o:turboDisplay.c ../../utils/tinygl.h ../../drivers/display.h ../../utils/task.h turboDisplay.h game.h buttonControl.h turboFood.h
	$(CC) -c $(CFLAGS) $< -o $@

turboFood.o: turboFood.c ../../utils/tinygl.h turboFood.h game.h
	$(CC) -c $(CFLAGS) $< -o $@

pio.o: ../../drivers/avr/pio.c ../../drivers/avr/pio.h ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

blueLed.o: blueLed.c ../../drivers/led.h blueLed.h
	$(CC) -c $(CFLAGS) $< -o $@

system.o: ../../drivers/avr/system.c ../../drivers/avr/system.h
	$(CC) -c $(CFLAGS) $< -o $@

timer.o: ../../drivers/avr/timer.c ../../drivers/avr/system.h ../../drivers/avr/timer.h
	$(CC) -c $(CFLAGS) $< -o $@

display.o: ../../drivers/display.c ../../drivers/avr/system.h ../../drivers/display.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

led.o: ../../drivers/led.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/led.h
	$(CC) -c $(CFLAGS) $< -o $@

ledmat.o: ../../drivers/ledmat.c ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/ledmat.h
	$(CC) -c $(CFLAGS) $< -o $@

navswitch.o: ../../drivers/navswitch.c ../../drivers/avr/delay.h ../../drivers/avr/pio.h ../../drivers/avr/system.h ../../drivers/navswitch.h
	$(CC) -c $(CFLAGS) $< -o $@

font.o: ../../utils/font.c ../../drivers/avr/system.h ../../utils/font.h
	$(CC) -c $(CFLAGS) $< -o $@

task.o: ../../utils/task.c ../../drivers/avr/system.h ../../drivers/avr/timer.h ../../utils/task.h
	$(CC) -c $(CFLAGS) $< -o $@

tinygl.o: ../../utils/tinygl.c ../../drivers/avr/system.h ../../drivers/display.h ../../utils/font.h ../../utils/tinygl.h
	$(CC) -c $(CFLAGS) $< -o $@

# Link: create ELF output file from object files.
game.out: game.o turbo.o demo.o blueLed.o buttonControl.o turboDisplay.o turboFood.o pio.o system.o timer.o display.o led.o ledmat.o navswitch.o font.o task.o tinygl.o
	$(CC) $(CFLAGS) $^ -o $@ -lm
	$(SIZE) $@


# Target: clean project.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex


# Target: program project.
.PHONY: program
program: game.out
	$(OBJCOPY) -O ihex game.out game.hex
	dfu-programmer atmega32u2 erase; dfu-programmer atmega32u2 flash game.hex; dfu-programmer atmega32u2 start


