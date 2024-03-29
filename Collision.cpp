#include "Collision.h"
#include "Game.h"

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB) {
	if (recA.x + recA.w > recB.x &&
		recB.x + recB.w > recA.x &&
		recA.y + recA.h > recB.y &&
		recB.y + recB.h > recA.y) {
		return true;
	}
	return false;
}

bool Collision::wallHit(const SDL_Rect& recA) {
	if (recA.x < 0 ||
		recA.x + recA.w > Game::WIN_WIDTH ||
		recA.y < 0 ||
		recA.y + recA.h > Game::WIN_HIGHT)
		return true;

	return false;
}