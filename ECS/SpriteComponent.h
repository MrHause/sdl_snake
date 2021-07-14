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

	bool isAnimated = false;
	int frames = 0;
	int speed = 100;
	uint32_t lastTime;
	uint32_t prevAnimTime;
	bool startAnim = false;
	bool animDirection = false;
	int animNum;

public:
	SpriteComponent() = default;
	SpriteComponent(const char* path) {
		setTex(path);
		previousComponent = nullptr;
	}

	SpriteComponent(const char* path, int mFrames, int mSpeed) {
		isAnimated = true;
		frames = mFrames;
		speed = mSpeed;
		setTex(path);
		animNum = 0;
		lastTime = SDL_GetTicks();
		previousComponent = nullptr;
	}

	SpriteComponent(const char* path, SpriteComponent* spriteComp) {
		setTex(path);
		setPreviouComponent(spriteComp);
	}

	~SpriteComponent() {
		SDL_DestroyTexture(texture);
	}
	
	void setPreviouComponent(SpriteComponent* spriteComp) {
		previousComponent = spriteComp;
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
		if (isAnimated) { 
			if (SDL_GetTicks() - lastTime > 3000) {
				if(!startAnim)
					prevAnimTime = SDL_GetTicks();
				startAnim = true;
			}

			if (startAnim) {
				if (SDL_GetTicks() - prevAnimTime > 300) {
					if (!animDirection)
						animNum++;
					else
						animNum--;

					prevAnimTime = SDL_GetTicks();
					srcRect.x = srcRect.w * animNum;
					if (animNum == (frames-1)) {
						animDirection = true;
					}
					if (animNum == 0) {
						lastTime = SDL_GetTicks();
						animDirection = false;
						startAnim = false;
					}
				}
			}
		}

		if (previousComponent == nullptr) {
			dstRect.x = static_cast<int>(transform->position.x);
			dstRect.y = static_cast<int>(transform->position.y);
		}else {
			dstRect.x = static_cast<int>(previousComponent->transform->previousPostion.x);
			dstRect.y = static_cast<int>(previousComponent->transform->previousPostion.y);
			transform->position.x = previousComponent->transform->previousPostion.x;
			transform->position.y = previousComponent->transform->previousPostion.y;
		}
		dstRect.w = transform->width * transform->scale;
		dstRect.h = transform->height * transform->scale;
	}

	void draw() override {
		TextureMenager::Draw(texture, srcRect, dstRect, transform->degree, SDL_FLIP_NONE);
	}
};