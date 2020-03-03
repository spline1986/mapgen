#include <SDL2/SDL.h>
#include "Tile.h"

Tile::Tile(const char *n, int i, Uint32 c) {
	Tile::name = n;
	Tile::code = i;
	Tile::color = c;
}
	
Tile::~Tile() {
}

int Tile::getCode() {
	return Tile::code;
}

Uint32 Tile::getColor() {
	return Tile::color;
}
