#pragma once

#include "Components.hpp"
#include "SDL.h"
#include "TextureManager.hpp"

class Sprite : public Component {
public:
	Sprite() = default;
	Sprite(const char* path) {
		setTex(path);
	}

	~Sprite() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureManager::loadTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<Transform>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->getWidth();
		srcRect.h = transform->getHeight();
		destRect.w = transform->getWidth() * transform->getScale();
		destRect.h = transform->getHeight() * transform->getScale();
	}

	void update() override {
		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->getWidth() * transform->getScale();
		destRect.h = transform->getHeight() * transform->getScale();
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect);
	}

private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
};