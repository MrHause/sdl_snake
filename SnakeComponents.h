#pragma once
#include "ECS/Components.h"
#include "SDL.h"

class SnakeComponents
{
private:
	Entity snakeHead;
	Entity food;
	Manager manager;
	std::vector<std::unique_ptr<Entity>> snakeTail;
public:
	SnakeComponents();
	SnakeComponents(int xpos, int ypos);
	~SnakeComponents(){}
	void draw();
	void refresh();
	void update();
	void addTailComponent();
};

