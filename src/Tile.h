#pragma once
#include <SDL2/SDL.h>

class Tile {
public:	
	Tile(const char *n, int i, Uint32 c);
	~Tile();
	int getCode();
	Uint32 getColor();
private:
	const char *name;
	int code;
	Uint32 color;
};
