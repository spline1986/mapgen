CC = g++
OBJS = mapgen.cpp src/Tile.cpp src/World.cpp
LINKER_OPTIONS = -lSDL2
OBJ_NAME = mapgen

all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_OPTIONS) -o $(OBJ_NAME)

clean:
	rm -f $(OBJ_NAME)