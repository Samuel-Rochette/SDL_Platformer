#pragma once

#include "Game.hpp"
#include "Components.hpp"

class SelectUI : public Component {
public:
	Transform* transform;
	Sprite* sprite;

	SelectUI(const char* uPath, const char* sPath, int sc) {
		unselectedPath = uPath;
		selectedPath = sPath;
		scene = sc;
	}

	void init() override {
		transform = &entity->getComponent<Transform>();
		sprite = &entity->getComponent<Sprite>();
		sprite->setTex(unselectedPath);
	}

	void update() override {
		if (isWithin(Game::mouse, sprite->getDest())) {
			sprite->setTex(selectedPath);
			if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
				Game::loadScene(scene);
		}
		else
			sprite->setTex(unselectedPath);
	}

	bool isWithin(Vector2D position, const SDL_Rect& rect) {
		//cout << "(" << position.x << ", " << position.y << ")" << endl;
		//cout << "(" << rect.x << ", " << rect.y << ")" << endl;
		if (position.x >= rect.x &&
			position.y >= rect.y &&
			position.x <= rect.x + rect.w &&
			position.y <= rect.y + rect.h)
			return true;

		return false;
	}

private:
	const char* unselectedPath;
	const char* selectedPath;
	int scene = 0;
};