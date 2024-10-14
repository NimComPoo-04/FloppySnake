CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb -std=c11 -O0 -pedantic

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

EXE=floppysnake.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^

clean:
	-del /Q $(OBJ) $(EXE)
	-rm $(OBJ) $(EXE)

.PHONY: all clean
