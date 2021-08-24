#include "Collision.hpp"

bool Collision::AABB(const SDL_Rect& rectA, const SDL_Rect& rectB) {
	if (
		rectA.x + rectA.w >= rectB.x &&
		rectB.x + rectB.w >= rectA.x &&
		rectA.y + rectA.h >= rectB.y &&
		rectB.y + rectB.h >= rectA.y
		)
	{
		return true;
	}

	return false;
}

bool Collision::AABB(const Collider& colA, const Collider& colB) {
	if (AABB(colA.collider, colB.collider)) {
		if (colA.tag == "player" && colB.tag == "tile") {
			int px = colA.transform->position.x;
			int py = colA.transform->position.y;
			int pw = colA.transform->getWidth();
			int ph = colA.transform->getHeight();

			int cx = colB.transform->position.x;
			int cy = colB.transform->position.y;
			int cw = colB.transform->getWidth();
			int ch = colB.transform->getHeight();

			if (px < cx && px + pw - cx < py + ph - cy && py + ph < cy + ch) {
				colA.transform->position.x = colB.transform->position.x - colA.transform->getWidth();
				colA.entity->getComponent<Sprite>().update();
				colA.entity->getComponent<PlayerController>().rwallstate = true;
			}
			else if (px > cx && cx + cw - px < py + ph - cy && py + ph < cy + ch) {
				colA.transform->position.x = colB.transform->position.x + colB.transform->getWidth();
				colA.entity->getComponent<Sprite>().update();
				colA.entity->getComponent<PlayerController>().lwallstate = true;
			}
			else if (cy > py && py + ph >= cy) {
				colA.transform->position.y = colB.transform->position.y - colA.transform->getHeight();
				colA.entity->getComponent<Sprite>().update();
				colA.entity->getComponent<PlayerController>().grounded = true;
			}
			else if (py > cy && cy + ch > py) {
				colA.transform->position.y = colB.transform->position.y + colB.transform->getHeight();
				colA.entity->getComponent<Sprite>().update();
				colA.transform->velocity.zero();
			}

		}
	}

	return false;
}