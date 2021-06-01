#include "Game.h"
#include "ECS/Components.h"
#include "TextureMenager.h"
#include "Collision.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "SnakeElements.h"

Game::Game() {}

Game::~Game() {}

SDL_Event Game::event;
SDL_Renderer* Game::gameRenderer;

Manager manager;
auto& snakeHead(manager.addEntity());
auto& food(manager.addEntity());

std::vector<std::unique_ptr<Entity>> snakeTail;

SnakeElements *snake;

void Game::init(const char* title, int xpos, int ypos, int width, int leght, bool fullScreen) {
	if (!SDL_Init(SDL_INIT_EVERYTHING)) {
		gameWindow = SDL_CreateWindow(title, xpos, ypos, width, leght, fullScreen);
		gameRenderer = SDL_CreateRenderer(gameWindow, -1, 0);
		if (gameWindow && gameRenderer) {
			SDL_SetRenderDrawColor(gameRenderer, 255, 255, 255, 255);
			isRunning = true;
		}
	}else {
		isRunning = false;
	}

	snake = new SnakeElements(&manager);
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	if (snake->detectFoodCollision()) {
		snake->snakeAddTailElement(&manager);
		snake->foodUpdatePosition();
	}

	manager.refresh();
	manager.update();
}

void Game::render() {
	SDL_RenderClear(gameRenderer);
	manager.draw();
	SDL_RenderPresent(gameRenderer);
}

void Game::clear() {

}
