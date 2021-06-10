#pragma once

#include "../Game.h"
#include "ECS.h"
#include "Components.h"

class KeyboardKontroller : public Component {
public:
	TransformComponent* transform;

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		transform->velocity.x = 1;
	}

	void update() override {
		if (Game::event.type == SDL_KEYDOWN) {
			switch (Game::event.key.keysym.sym) {
			case SDLK_w:
				if (transform->velocity.y != 1) {
					transform->velocity.x = 0;
					transform->velocity.y = -1;
					transform->degree = 270.0;
				}
				break;
			case SDLK_a:
				if (transform->velocity.x != 1) {
					transform->velocity.y = 0;
					transform->velocity.x = -1;
					transform->degree = 180;
				}
				break;
			case SDLK_d:
				if (transform->velocity.x != -1) {
					transform->velocity.y = 0;
					transform->velocity.x = 1;
					transform->degree = 0;
				}
				break;
			case SDLK_s:
				if (transform->velocity.y != -1) {
					transform->velocity.x = 0;
					transform->velocity.y = 1;
					transform->degree = 90.0;
				}
				break;
			default:
				break;
			}
		}
	}
};