#pragma once
#include "ECS/Components.h"
#include "SDL.h"
#include <vector>

class SnakeElements
{
private:
	Entity& snakeHead;
	Entity& food;
	std::vector<std::unique_ptr<Entity>> snakeTail;
	std::vector<ColliderComponent*> tailColiders;

public:
	SnakeElements(Manager* manager);
	~SnakeElements(){}
	void snakeAddTailElement(Manager* manager);
	void foodUpdatePosition();
	bool detectFoodCollision();
	bool detectWallCollision();
	bool detectTailCollision();
	void destroySnakeComponnets();
};

