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

	void init() override {
		if (!entity->hasComponent<Transform>())
			entity->addComponent<Transform>();
	
		transform = &entity->getComponent<Transform>();

		Game::colliders.push_back(this);
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->getWidth() * transform->getScale();
		collider.h = transform->getHeight() * transform->getScale();
	}
};