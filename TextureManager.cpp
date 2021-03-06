#include "TextureManager.hpp"

SDL_Texture* TextureManager::loadTexture(const char* texture) {
	SDL_Surface* tempSurface = IMG_Load(texture);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return tex;
}

void TextureManager::draw(SDL_Texture* tex, SDL_Rect srcRect, SDL_Rect destRect, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::renderer, tex, &srcRect, &destRect, NULL, NULL, flip);
}