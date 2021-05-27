#pragma once

#include "Components.h"
#include "../Vector2D.h"

class TransformComponent : public Component {
public:
	Vector2D position;
	Vector2D previousPostion;
	Vector2D velocity;
	
	int height = 20;
	int width = 20;
	int scale = 1;

	int speed = 20;

	TransformComponent() {
		position.Zero();
	}

	TransformComponent(int scl) {
		position.Zero();
		scale = scl;
	}

	TransformComponent(int x, int y) {
		position.x = x;
		position.y = y;
	}

	TransformComponent(int x, int y, int w, int h, int scl) {
		position.x = x;
		position.y = y;
		previousPostion.x = x;
		previousPostion.y = y;
		height = h;
		width = w;
		scale = scl;
	}

	Vector2D getTransformPosition() {
		return position;
	}

	void init() override {
		velocity.Zero();
	}

	void update() override {
		previousPostion.x = position.x;
		previousPostion.y = position.y;
		position.x += velocity.x * speed;
		position.y += velocity.y * speed;
	}
};
