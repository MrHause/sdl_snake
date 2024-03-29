#include "Game.h"
#include "ECS/Components.h"
#include "TextureMenager.h"
#include "Collision.h"
#include <time.h>
#include <stdlib.h>
#include <vector>
#include "SnakeElements.h"

#include "GameStates.h"
#include "GameEnd.h"

Manager manager;

SnakeElements *snake;

Game::Game() {
	snake = new SnakeElements(&manager);
}

Game::~Game() {
	delete snake;
}

void Game::update() {
	if (snake->detectFoodCollision()) {
		snake->snakeAddTailElement(&manager);
		snake->foodUpdatePosition();
	}

	if (snake->detectWallCollision()) {
		snake->destroySnakeComponnets();
		manager.refresh();
		this->context_->TransitionTo(new GameEnd("assets/gameOver.png"));
		std::cout << "WALL HIT" << std::endl;
		return;
	}

	if (snake->detectTailCollision()) {
		snake->destroySnakeComponnets();
		manager.refresh();
		this->context_->TransitionTo(new GameEnd("assets/gameOver.png"));
		std::cout << "TAIL HIT" << std::endl;
		return;
	}

	manager.refresh();
	manager.update();
}

auto& foods(manager.getGroup(Game::groupFood));
auto& snakeEl(manager.getGroup(Game::groupSnake));

void Game::render() {
	SDL_RenderClear(GameContext::gameRenderer);
	//manager.draw();
	for (auto& f : foods) {
		f->draw();
	}
	for (auto& s : snakeEl) {
		s->draw();
	}
	SDL_RenderPresent(GameContext::gameRenderer);
}

void Game::clear() {
	if(snake)
		delete snake;
}
