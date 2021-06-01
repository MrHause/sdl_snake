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
	/*
	srand(time(NULL));

	int food_xpos, food_ypos;
	food_xpos = ((rand() % 780 + 1) / 20) * 20;
	food_ypos = ((rand() % 620 + 1) / 20) * 20;

	snakeHead.addComponent<TransformComponent>(300.0f, 300.0f, 20, 20, 1);
	snakeHead.addComponent<KeyboardKontroller>();
	snakeHead.addComponent<SpriteComponent>("assets/grass.png");
	snakeHead.addComponent<ColliderComponent>("head");

	food.addComponent<TransformComponent>((float)food_xpos, (float)food_ypos, 20, 20, 1);
	food.addComponent<FoodComponent>("assets/water.png");
	food.addComponent<ColliderComponent>("food");
	*/

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
	/*
	if (Collision::AABB(snakeHead.getComponent<ColliderComponent>().collider, food.getComponent<ColliderComponent>().collider)) {
		//!! add update food transform component
		Vector2D currentFoodPosition = food.getComponent<TransformComponent>().getTransformPosition();
		std::cout << "hit food" << std::endl;
		int food_xpos, food_ypos;
		food_xpos = ((rand() % 780 + 1) / 20) * 20;
		food_ypos = ((rand() % 620 + 1) / 20) * 20;
		food.getComponent<FoodComponent>().updateFoodPosition(food_xpos, food_ypos);

		auto& newTailElement(manager.addEntity());
		std::unique_ptr<Entity> uPtr{ &newTailElement };
		snakeTail.emplace_back(std::move(uPtr));
		unsigned int len = snakeTail.size();
		snakeTail.at(len - 1)->addComponent<TransformComponent>((float)currentFoodPosition.x, (float)currentFoodPosition.y, 20, 20, 1);
		snakeTail.at(len - 1)->addComponent<SpriteComponent>("assets/dirt.png", &snakeHead.getComponent<SpriteComponent>());
		if (len > 1) {
			snakeTail.at(len - 2)->getComponent<SpriteComponent>().setPreviouComponent(&snakeTail.at(len - 1)->getComponent<SpriteComponent>());
		}
	}
	*/
	if (snake->detectFoodCollision()) {
		snake->foodUpdatePosition();
		snake->snakeAddTailElement(&manager);
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
