#include "SnakeElements.h"
#include <time.h>
#include <stdlib.h>
#include "Collision.h"

SnakeElements::SnakeElements(Manager* manager) : snakeHead(manager->addEntity()), food(manager->addEntity()) {
	//snakeHead = manager->addEntity();
	//food = manager->addEntity();
	snakeHead.addComponent<TransformComponent>(240.0f, 200.0f, Game::ELEMENT_WIDTH, Game::ELEMENT_HIGHT, 1);
	snakeHead.addComponent<KeyboardKontroller>();
	snakeHead.addComponent<SpriteComponent>("assets/head.png");
	snakeHead.addComponent<ColliderComponent>("head");

	srand(time(NULL));

	int food_xpos, food_ypos;
	food_xpos = ((rand() % (Game::WIN_WIDTH - Game::ELEMENT_WIDTH) + 1) / Game::ELEMENT_WIDTH) * Game::ELEMENT_WIDTH;
	food_ypos = ((rand() % (Game::WIN_HIGHT - Game::ELEMENT_HIGHT) + 1) / Game::ELEMENT_HIGHT) * Game::ELEMENT_HIGHT;
	food.addComponent<TransformComponent>((float)food_xpos, (float)food_ypos, Game::ELEMENT_WIDTH, Game::ELEMENT_HIGHT, 1);
	food.addComponent<FoodComponent>("assets/food.png");
	food.addComponent<ColliderComponent>("food");
}

void SnakeElements::foodUpdatePosition() {
	int food_xpos, food_ypos;
	food_xpos = ((rand() % (Game::WIN_WIDTH - Game::ELEMENT_WIDTH) + 1) / Game::ELEMENT_WIDTH) * Game::ELEMENT_WIDTH;
	food_ypos = ((rand() % (Game::WIN_HIGHT - Game::ELEMENT_HIGHT) + 1) / Game::ELEMENT_HIGHT) * Game::ELEMENT_HIGHT;
	food.getComponent<FoodComponent>().updateFoodPosition(food_xpos, food_ypos);
}

bool SnakeElements::detectFoodCollision() {
	if (Collision::AABB(snakeHead.getComponent<ColliderComponent>().collider, food.getComponent<ColliderComponent>().collider)) {
		return true;
	}
	return false;
}

bool SnakeElements::detectWallCollision() {
	if (Collision::wallHit(snakeHead.getComponent<ColliderComponent>().collider))
		return true;
	return false;
}

void SnakeElements::snakeAddTailElement(Manager *manager) {
	//Vector2D currentFoodPosition = food.getComponent<TransformComponent>().getTransformPosition();
	Vector2D currentFoodPosition;
	if(snakeTail.size() > 0)
		currentFoodPosition  = snakeTail.at(0)->getComponent<TransformComponent>().getTransformPosition();
	else
		currentFoodPosition = snakeHead.getComponent<TransformComponent>().getTransformPosition();

	auto& newTailElement(manager->addEntity());
	std::unique_ptr<Entity> uPtr{ &newTailElement };
	snakeTail.emplace_back(std::move(uPtr));
	unsigned int len = snakeTail.size();
	snakeTail.at(len - 1)->addComponent<TransformComponent>((float)currentFoodPosition.x, (float)currentFoodPosition.y, Game::ELEMENT_WIDTH, Game::ELEMENT_HIGHT, 1);
	if(len == 1)
		snakeTail.at(len - 1)->addComponent<SpriteComponent>("assets/water.png", &snakeHead.getComponent<SpriteComponent>());
	else
		snakeTail.at(len - 1)->addComponent<SpriteComponent>("assets/water.png", &snakeTail.at(len - 2)->getComponent<SpriteComponent>());

	std::string coliderTag = "tail" + std::to_string(snakeTail.size());
	snakeTail.at(len - 1)->addComponent<ColliderComponent>(coliderTag);
	tailColiders.push_back(&snakeTail.at(len - 1)->getComponent<ColliderComponent>());
}

bool SnakeElements::detectTailCollision() {
	for (auto col : tailColiders) {
		if (Collision::AABB(snakeHead.getComponent<ColliderComponent>().collider, col->collider)) {
			return true;
		}
	}
	return false;
}

void SnakeElements::destroySnakeComponnets() {
	snakeHead.destroy();
	for (auto& tailEntity : snakeTail) {
		tailEntity->destroy();
	}
	food.destroy();
}
