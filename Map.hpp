#pragma once
#include "Game.hpp"

class Map {
public:
	Map();
	~Map();

	void loadMap(int arr[20][25]);
	void drawMap();

private:
	SDL_Rect srcRect, destRect;

	SDL_Texture* background;
	SDL_Texture* floor;

	int map[20][25];
	
};