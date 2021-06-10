#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Game
{
public:
	enum winParam {
		WIN_WIDTH = 420,
		WIN_HIGHT = 600,
		ELEMENT_WIDTH = 20,
		ELEMENT_HIGHT = 20
	};

	Game();
	~Game();

	void init(const char *title, int xpos, int ypos, int width, int leght, bool fullScreen);
	void update();
	void render();
	void clear();
	void handleEvents();
	bool isGameRunning() { return isRunning; }

	static SDL_Renderer* gameRenderer;
	static SDL_Event event;
private:
	SDL_Window* gameWindow;
	bool isRunning;
};

