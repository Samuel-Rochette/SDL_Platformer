#pragma once
#include <string>
#include "SDL.h"
#include "Components.hpp"

class Collider : public Component {
public:
	SDL_Rect collider;
	string tag;

	Transform* transform;

	Collider(string t) {
		tag = t;
	}

	Collider(string t, int w, int h) {
		tag = t;

		width = w;
		height = h;
	}

	void init() override {
		if (!entity->hasComponent<Transform>())
			entity->addComponent<Transform>();
		transform = &entity->getComponent<Transform>();

		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		
		if (width > 0)
			collider.w = width;
		else
			collider.w = transform->getWidth() * transform->getScale();
		
		if (height > 0)
			collider.h = height;
		else
			collider.h = transform->getHeight() * transform->getScale();

		Game::colliders.push_back(this);
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
	}

private:
	int xOffset = 0;
	int yOffset = 0;
	int width = 0;
	int height = 0;
};