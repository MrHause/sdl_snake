#define SDL_MAIN_HANDLED
#include "SDL.h"
#include "Game.h"

Game* game = nullptr;

int main() {
	const int FPS = 10;
	const int FrameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("gameTest", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Game::WIN_WIDTH, Game::WIN_HIGHT, false);

	while (game->isGameRunning()) {
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;
		if (FrameDelay > frameTime) {
			SDL_Delay(FrameDelay - frameTime);
		}
	}

	game->clear();
	return 0;
}