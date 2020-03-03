#include <ctime>
#include <iostream>
#include <SDL2/SDL.h>

#include "src/World.h"

using namespace std;

const int fps = 30;
SDL_Window *window = NULL;
SDL_Surface *surface = NULL;

Tile *water = new Tile("water", 0, 0x0000FF);
Tile *grass = new Tile("grass", 1, 0x00FF00);

bool init() {
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
		success = false;
	} else {
		window = SDL_CreateWindow("Map generator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 512, 512, 0);
		if (window == NULL) {
			cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
			success = false;
		}
	}
	return success;
}

int main(int argc, char** argv) {
	bool quit = false;
	int size = 128;
	World *map = new World(size, grass, water);
	SDL_Event e;
	SDL_Rect rect;

	if (init()) {
		surface = SDL_GetWindowSurface(window);
		while (!quit) {
			for (int x = 0; x < size; x++)
				for (int y = 0; y < size; y++){
					rect.x = x*4; rect.y = y*4; rect.w = 4; rect.h = 4;
					SDL_FillRect(surface, &rect, map->getTile(x, y)->getColor());
				}
			SDL_UpdateWindowSurface(window);
			if (SDL_PollEvent(&e) != 0) {
				if (e.type == SDL_QUIT) {
					quit = true;
				} else if (e.type == SDL_KEYDOWN) {
					int key = e.key.keysym.sym;
					switch (key) {
					case SDLK_ESCAPE:
						quit = true;
						break;
					case SDLK_SPACE:
						map->generateWorld(size, grass, water);
						break;
					}
				}
			}
			SDL_Delay(1000 / fps);
		}
	}
	return 0;
}
