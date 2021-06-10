#include "TextureMenager.h"

SDL_Texture* TextureMenager::loadTexture(const char* path) {
	SDL_Surface* surface = IMG_Load(path);
	SDL_Texture* newTexutre = SDL_CreateTextureFromSurface(Game::gameRenderer, surface);
	SDL_free(surface);
	return newTexutre;
}

void TextureMenager::Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dst, float angle, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(Game::gameRenderer, text, &src, &dst, angle, NULL, flip);
}
