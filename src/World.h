#pragma once
#include <vector>
#include "Tile.h"

class World {
public:
	World(int size, Tile *tile1, Tile *tile2);
	~World();
	void generateWorld(int size, Tile *tile1, Tile *tile2);
	Tile * getTile(int x, int y);
private:
	void fillRegion(int x, int y, int n, Tile *tile);
	std::vector<std::vector<Tile*>> createWorld(int size, Tile *tile);
	void startWorld(int size, Tile *tile1, Tile *tile2);
	void buildWorld(int size, Tile *tile1, Tile *tile2);
	int checkWorld(int size);
	void worldGoodizer(int size, Tile *tile1, Tile *tile2, int i);
	std::vector<std::vector<Tile*>> map;
};
