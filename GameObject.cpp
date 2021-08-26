#include "GameObject.hpp"
#include "TextureManager.hpp"

GameObject::GameObject(const char* texturesheet, int x, int y) {
	objTexture = TextureManager::loadTexture(texturesheet);

	xpos = x;
	ypos = y;
}

void GameObject::update() {
	xpos++;
	ypos++;

	srcRect.w = 128;
	srcRect.h = 128;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = 64;
	destRect.h = 64;
	destRect.x = xpos;
	destRect.y = ypos;
}

void GameObject::render() {
	SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}