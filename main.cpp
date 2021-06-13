#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Game.h"
#include "GameStates.h"

//Game* game = nullptr;

GameContext* game = nullptr;

int main() {
	const int FPS = 10;
	const int FrameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new GameContext();
	game->gameInit("gameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::WIN_WIDTH, Game::WIN_HIGHT, false);
	game->TransitionTo(new Game);
	while (game->getGameState() == GameContext::gameRunning) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (FrameDelay > frameTime) {
			SDL_Delay(FrameDelay - frameTime);
		}
	}

	//game->clear();
	delete game;
	return 0;
}