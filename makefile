CC = gcc
INCLUDE = include
SRC = src
BIN = bin

EXE_NAME = yt-mpv

C_FILES = $(wildcard $(SRC)/*.c)
C_OBJS = $(patsubst $(SRC)/%.c, $(BIN)/%.o, $(C_FILES))

COM_FILES = $(wildcard $(SRC)/commands/*.c)
COM_OBJ = $(patsubst $(SRC)/commands/%.c, $(BIN)/%.o, COM_FILES)

C_WARN = -Wextra -Wall -Wshadow -Wundef -fno-common -Wconversion -Wpadded -Wpedantic
C_FLAGS = -v -Os -std=c2x -D_DEFAULT_SOURCE
INCLUDE_DIR = -I$(INCLUDE)/ 
C_ALL = $(C_WARN) $(C_FLAGS) $(INCLUDE_DIR)

all: dirs $(C_OBJS) $(COM_OBJS) link

dirs:
	mkdir -p bin

$(BIN)/%.o: $(SRC)/%.c
	$(CC) $(C_ALL) -c $< -o $@

link:
	$(CC) -o $(EXE_NAME) $(BIN)/*.o

c:
	rm $(BIN)/*.o
	rm $(EXE_NAME)

r: c all
