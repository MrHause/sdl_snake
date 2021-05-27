#pragma once

#include "Components.h"
#include "SDL.h"
#include "../TextureMenager.h"
#include "TransformComponent.h"

class SpriteComponent : public Component {
private:
	SpriteComponent* previousComponent;
	TransformComponent* transform;
	Vector2D prevPosition;
	SDL_Texture* texture;
	SDL_Rect srcRect, dstRect;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
		previousComponent = nullptr;
	}

	SpriteComponent(const char* path, SpriteComponent* spriteComp) {
		setTex(path);
		previousComponent = spriteComp;
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}

	void setTex(const char* path) {
		texture = TextureMenager::loadTexture(path);
	}

	void init() override {
		transform = &entity->getComponent<TransformComponent>();

		srcRect.x = srcRect.y = 0;
		srcRect.w = transform->width;
		srcRect.h = transform->height;
	}

	void  update() override {
		if (previousComponent == nullptr) {
			dstRect.x = static_cast<int>(transform->position.x);
			dstRect.y = static_cast<int>(transform->position.y);
		}else {
			dstRect.x = static_cast<int>(previousComponent->transform->previousPostion.x);
			dstRect.y = static_cast<int>(previousComponent->transform->previousPostion.y);
		}
		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureMenager::Draw(texture, srcRect, dstRect);
	}
};