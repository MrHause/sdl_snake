#pragma once
#include <iostream>
#include "SDL.h"

class GameContext;

class GameStates
{
protected:
	GameContext* context_;

public:
	virtual ~GameStates() {
	}

	void setContext(GameContext* context) {
		this->context_ = context;
	}

	virtual void update() = 0;
	virtual void render() = 0;
	virtual void clear() = 0;
};

class GameContext {	
public:
	enum gameState_t {
		gameRunning = 0,
		gamePaused,
		gameEnd
	};

	static SDL_Renderer* gameRenderer;
	static SDL_Event event;

	GameContext() : state_(nullptr){
		gameState = GameContext::gamePaused;
	}

	GameContext(GameStates* state) : state_(nullptr) {
		this->TransitionTo(state);
		gameState = GameContext::gamePaused;
	}
	~GameContext() {
		delete state_;
	}

	bool isGameRunning() { return isRunning; }

	gameState_t getGameState() { return gameState; }

	void setGameState(gameState_t mGameState) { gameState = mGameState; }

	void TransitionTo(GameStates* state) {
		//std::cout << "Context: Transition to " << typeid(*state).name() << ".\n";
		if (this->state_ != nullptr)
			delete this->state_;
		this->state_ = state;
		this->state_->setContext(this);
	}

	void gameInit(const char* title, int xpos, int ypos, int width, int leght, bool fullScreen);

	void update() {
		this->state_->update();
	}

	void render() {
		this->state_->render();
	}

	void handleEvents();

private:
	GameStates* state_;
	SDL_Window* gameWindow;
	bool isRunning;
	gameState_t gameState;
};

