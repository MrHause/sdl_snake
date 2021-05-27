#pragma once

#include "Components.h"
#include "SDL.h"
#include "TransformComponent.h"

class FoodComponent : public Component {
private:
	SDL_Rect srcRect, dstRect;
	SDL_Texture* texture;
	TransformComponent* transform;

	void setFoodPosition() {
		dstRect.x = transform->position.x;
		dstRect.y = transform->position.y;
		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
	}

public:
	FoodComponent(const char* texturePath){
		texture = TextureMenager::loadTexture(texturePath);
	}

	void updateFoodPosition(int xpos, int ypos) {
		dstRect.x = transform->position.x = xpos;
		dstRect.y = transform->position.y = ypos;
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();
		srcRect.x = 0;
		srcRect.x = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
		setFoodPosition();
	}

	void draw() override {
		TextureMenager::Draw(texture, srcRect, dstRect);
	}
};
