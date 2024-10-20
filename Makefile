CC = gcc
CFLAGS = -Wall -Wextra -Werror -ggdb -std=c11 -O0 -pedantic 

SRC=$(wildcard *.c)
OBJ=$(patsubst %.c, %.o, $(SRC))

ifeq ($(OS), Windows_NT)
LIB = -Llib/raylib-5.0_win64_mingw-w64/lib -lraylib -lopengl32 -lgdi32 -lwinmm -mwindows
INC = -Ilib/raylib-5.0_win64_mingw-w64/include
RM = del /Q
else
LIB = -Llib/raylib-5.0_linux_amd64/lib -lraylib -lm
INC = -Ilib/raylib-5.0_linux_amd64/include
RM = rm
endif

EXE=floppysnake.exe

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INC)

clean:
	$(RM) $(OBJ) $(EXE)

.PHONY: all clean
