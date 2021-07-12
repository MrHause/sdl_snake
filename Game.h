#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include "GameStates.h"

class Game : public GameStates
{
public:
	enum winParam {
		WIN_WIDTH = 420,
		WIN_HIGHT = 600,
		ELEMENT_WIDTH = 20,
		ELEMENT_HIGHT = 20
	};

	enum gameGroups {
		groupFood = 0,
		groupSnake,
		groupColliders
	};

	Game();
	~Game();

	void update();
	void render();
	void clear();
private:
};

