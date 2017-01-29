SRC = main.cpp
CC = arduino
BOARD = arduino:avr:atmega328



all: upload

upload:
	-$(CC)  --upload --board $(BOARD) $(SRC)

verify:
	-$(CC)  --verify --board $(BOARD) $(SRC)
