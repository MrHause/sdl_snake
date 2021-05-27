#pragma once
#include "SDL.h"
#include "SDL_image.h"

class Game
{
public:
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

