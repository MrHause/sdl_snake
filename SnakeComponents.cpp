#include "SnakeComponents.h"
#include <time.h>
#include <stdlib.h>

SnakeComponents::SnakeComponents() {
	snakeHead = manager.addEntity();
	snakeHead.addComponent<TransformComponent>(300.0f, 300.0f, 20, 20, 1);
	snakeHead.addComponent<KeyboardKontroller>();
	snakeHead.addComponent<SpriteComponent>("assets/grass.png");
	snakeHead.addComponent<ColliderComponent>("head");

	srand(time(NULL));
	food = manager.addEntity();
	food.addComponent<TransformComponent>((float)food_xpos, (float)food_ypos, 20, 20, 1);
	food.addComponent<FoodComponent>("assets/water.png");
	food.addComponent<ColliderComponent>("food");

}

SnakeComponents::SnakeComponents(int xpos, int ypos) {
	snakeHead = manager.addEntity();
	snakeHead.addComponent<TransformComponent>((float)xpos, (float)ypos, 20, 20, 1);
	snakeHead.addComponent<KeyboardKontroller>();
	snakeHead.addComponent<SpriteComponent>("assets/grass.png");
	snakeHead.addComponent<ColliderComponent>("head");
}

void SnakeComponents::draw() {
	manager.draw();
}

void SnakeComponents::refresh() {
	manager.draw();
}

void SnakeComponents::update() {
	manager.update();
}

void SnakeComponents::addTailComponent() {

}


