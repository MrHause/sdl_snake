#pragma once
#include "Game.h"

class TextureMenager
{
public:
	static SDL_Texture* loadTexture(const char* path);
	static void Draw(SDL_Texture* text, SDL_Rect src, SDL_Rect dst, float angle, SDL_RendererFlip flip);
};

