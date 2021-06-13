#pragma once

#include "SDL.h"
#include "GameStates.h"
#include "TextureMenager.h"

class GameEnd : public GameStates {
private:
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

public:
	GameEnd(const char *path){
		texture = TextureMenager::loadTexture(path);
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = 300;
		srcRect.h = 150;
		dstRect.w = srcRect.w;
		dstRect.h = srcRect.h;
		dstRect.x = 60;
		dstRect.y = 150;
	}

	~GameEnd(){
	}

	void update() override {
		dstRect.x = 60;
		dstRect.y = 120;
	}

	void render() override {
		if (keyboardHandler())
			return;
		SDL_RenderClear(GameContext::gameRenderer);
		TextureMenager::Draw(texture, srcRect, dstRect, 0.0f, SDL_FLIP_NONE);
		SDL_RenderPresent(GameContext::gameRenderer);
	}

	void clear() override {
	}

	bool keyboardHandler() {
		if (GameContext::event.type == SDL_KEYDOWN) {
			switch (GameContext::event.key.keysym.sym) {
			case SDLK_SPACE:
				this->context_->TransitionTo(new Game);
				return true;
				break;
			default:
				break;
			}
		}
		return false;
	}
};
