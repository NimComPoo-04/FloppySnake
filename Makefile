CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb -std=c11 -O0 -pedantic 

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

LIB = -Llib/raylib-5.0_linux_amd64/lib -lraylib
INC = -Ilib/raylib-5.0_linux_amd64/include

RM = rm

ifneq ($(OS), Windows_NT)
LIB += -lm
RM = del /Q
endif

EXE=floppysnake.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INC)

clean:
	-del /Q $(OBJ) $(EXE)
	-rm $(OBJ) $(EXE)

.PHONY: all clean
