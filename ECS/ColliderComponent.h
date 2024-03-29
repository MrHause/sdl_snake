#pragma once

#include <string>
#include "ECS.h"
#include "SDL.h"
#include "Components.h"

class ColliderComponent : public Component {
public:
	SDL_Rect collider;
	std::string tag;
	TransformComponent* transform;

	ColliderComponent(std::string name) {
		tag = name;
	}

	void init() {
		if (!entity->hasComponent<TransformComponent>()) {
			entity->addComponent<TransformComponent>();
		}
		transform = &entity->getComponent<TransformComponent>();
	}

	void update() override {
		collider.x = static_cast<int>(transform->position.x);
		collider.y = static_cast<int>(transform->position.y);
		collider.w = transform->width * transform->scale;
		collider.h = transform->height * transform->scale;
	}
};