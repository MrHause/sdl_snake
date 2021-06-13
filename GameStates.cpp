#include "GameStates.h"
#include "SDL.h"

SDL_Renderer* GameContext::gameRenderer;
SDL_Event GameContext::event;

void GameContext::gameInit(const char* title, int xpos, int ypos, int width, int leght, bool fullScreen) {
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		gameWindow = SDL_CreateWindow(title, xpos, ypos, width, leght, fullScreen);
		gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
		if (gameWindow && gameRenderer) {
			SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
			isRunning = true;
			setGameState(gameRunning);
		}
	}
	else {
		isRunning = false;
		setGameState(gameEnd);
	}
}

void GameContext::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		setGameState(gameEnd);
		break;
	default:
		break;
	}
}
