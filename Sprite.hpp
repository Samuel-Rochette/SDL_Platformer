#pragma once

#include "Components.hpp"
#include "SDL.h"
#include "TextureManager.hpp"
#include "Animation.hpp"
#include <map>

class Sprite : public Component {
public:
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	bool animated = false;

	Sprite() = default;
	Sprite(const char* path) {
		setTex(path);
	}

	Sprite(const char* path, bool isAnimated) {
		setTex(path);
		animated = isAnimated;
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
		if (animated)
			srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / animSpeed) % animFrames);
	
		srcRect.y = animIndex * srcRect.h;

		destRect.x = static_cast<int>(transform->position.x);
		destRect.y = static_cast<int>(transform->position.y);
		destRect.w = transform->getWidth() * transform->getScale();
		destRect.h = transform->getHeight() * transform->getScale();
	}

	void draw() override {
		TextureManager::draw(texture, srcRect, destRect, flip);
	}

	void addAnimation(const char* name, int index, int frames, int speed) {
		animations[name] = Animation(index, frames, speed);
	}

	void playAnimation(const char* name) {
		animFrames = animations[name].frames;
		animSpeed = animations[name].speed;
		animIndex = animations[name].index;
	}

	SDL_Rect& getDest() { return destRect; }

private:
	Transform* transform;
	SDL_Texture* texture;
	SDL_Rect srcRect, destRect;
	map<const char*, Animation> animations;
	int animFrames = 1;
	int animSpeed = 100;
	int animIndex = 0;
};