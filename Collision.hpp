#pragma once
#include <SDL.h>
#include "Collider.hpp"

class Collider;

class Collision {
public:
	static bool AABB(const SDL_Rect& rectA, const SDL_Rect& rectB);
	static bool AABB(const Collider& colA, const Collider& colB);
};