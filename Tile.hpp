#pragma once

#include "ECS.hpp"
#include "Transform.hpp"
#include "Sprite.hpp"
#include "SDL.h"

class Tile : public Component {
public:
	Transform* transform;
	Sprite* sprite;

	SDL_Rect tileRect;
	int tileID;
	const char* path;

	Tile() = default;

	Tile(int x, int y, int w, int h, int id) {
		tileRect.x = x;
		tileRect.y = y;
		tileRect.w = w;
		tileRect.h = h;
		tileID = id;
	
		switch (tileID) {
		case 0:
			path = "assets/background.png";
			break;
		case 1:
			path = "assets/floor.png";
			break;
		default:
			break;
		}
	}

	void init() override {
		entity->addComponent<Transform>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
		transform = &entity->getComponent<Transform>();

		entity->addComponent<Sprite>(path);
		sprite = &entity->getComponent<Sprite>();
	}
};