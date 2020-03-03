#include <ctime>
#include <vector>
#include "Tile.h"
#include "World.h"

void World::fillRegion(int x, int y, int n, Tile *tile) {
	for (int i = x; i <= x + n; i++)
		for (int j = y; j <= y + n; j++)
			World::map[i][j] = tile;
}

int World::checkWorld(int size) {
	int t = 0;
	for (int x = 0; x < size; x++)
		for(int y = 0; y < size; y++)
			if (World::map[x][y]->getCode() == 1)
				t++;
	return t;
}

std::vector<std::vector<Tile*>> World::createWorld(int size, Tile *tile) {
	std::vector<std::vector<Tile*>> nmap;
	for (int x = 0; x < size; x++) {
		nmap.push_back(std::vector<Tile*>());
		for (int y = 0; y < size; y++)
			nmap[x].push_back(tile);
	}
	return nmap;
}

void World::startWorld(int size, Tile *tile1, Tile *tile2) {
	int n = 8;
	int step = size / n;
	World::map = World::createWorld(size, tile1);
	for (int i = 0; i + step < size; i = i + step) {
			World::fillRegion(i, 0, step, tile2);
			World::fillRegion(i, size - step - 1 , step, tile2);
			World::fillRegion(0, i, step, tile2);
			World::fillRegion(size - step - 1, i, step, tile2);
	}
	World::fillRegion(size - step - 1, size - step - 1, step, tile2);
	World::fillRegion(size / 2 - step - 1, size / 2 - step - 1, step * 2, tile2);
}

void World::buildWorld(int size, Tile *tile1, Tile *tile2) {
	int i = 16;
	int n;
	n = size / i;
	World::startWorld(size, tile1, tile2);
	srand(clock());
	while (n > 0) {
		for (int x = 0; x < size; x = x + n)
			for (int y = 0; y < size; y = y + n) {
				if (x + n < size && y + n < size) {
					int t, dx, dy = 0;
					t = rand() % 2;
					if (t == 0)
						dx = (x + n);// / (n * 2) * n * 2;
					else
						dx = (x - n);// / (n * 2) * n * 2;
					t = rand() % 2;
					if (t == 0)
						dy = (y + n);// / (n * 2) * n * 2;
					else
						dy = (y - n);// / (n * 2) * n * 2;
					if (dx >= size) dx = 0;
					if (dx < 0) dx = size - n;
					if (dy >= size) dy = 0;
					if (dy < 0) dy = size - n;
					if (x < size && y < size)
						World::fillRegion(x, y, n, World::map[dx][dy]);
				}
			}
		n = n / 2;
	}
}

void World::worldGoodizer(int size, Tile *tile1, Tile *tile2, int i) {
	std::vector<std::vector<Tile*>> nmap;
	nmap = createWorld(size, tile1);
	for (int n = 0; n < i; n++)
		for (int x = 0; x < size; x++)
			for (int y = 0; y < size; y++) {
				int c = 0;
				for (int dx = x - 3; dx <= x + 3; dx++)
					for(int dy = y - 3; dy <= y + 3; dy++)
						if (dx >= 0 && dy >= 0 && dx < size && dy < size) {
							if (World::map[dx][dy] == tile1)
								c++;
							if (c > 30)
								nmap[x][y] = tile1;
							else
								nmap[x][y] = tile2;
						}
			}
	World::map = nmap;
}

void World::generateWorld(int size, Tile *tile1, Tile *tile2) {
	int t = 0;
	while (t < size*size/2.1 || t > size*size/1.9) {
		this->buildWorld(size, tile1, tile2);
		t = this->checkWorld(size);
	}
	this->worldGoodizer(size, tile1, tile2, 3);
}

Tile * World::getTile(int x, int y) {
	return World::map[x][y];
}

World::World(int size, Tile *tile1, Tile *tile2) {
	this->generateWorld(size, tile1, tile2);
}

World::~World() {
}
