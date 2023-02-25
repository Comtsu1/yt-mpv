CC = gcc
INCLUDE = include
SRC = src
BIN = bin

EXE_NAME = yt-mpv

C_FILES = $(wildcard $(SRC)/*.c)
C_OBJS = $(patsubst %.c, %.o, $(wildcard $(SRC)/*.c))

C_WARN = -Wextra -Wall -Wshadow -Wundef -fno-common -Wconversion -Wpadded -Wpedantic
C_FLAGS = -v -Os -std=c17 -I$(INCLUDE)
C_ALL = $(C_WARN) $(C_FLAGS)

all: dirs $(C_OBJS) link

dirs:
	mkdir -p bin

%.o: %.c
	$(CC) $(C_ALL) -c $< -o $@
	mv $@ $(BIN)/

link:
	$(CC) -o $(EXE_NAME) $(BIN)/*.o

c:
	rm $(BIN)/*.o
	rm $(EXE_NAME)
