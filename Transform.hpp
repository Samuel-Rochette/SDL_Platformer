#pragma once

#include "Components.hpp"
#include "Vector2D.hpp"

class Transform : public Component {
public:

	Vector2D position;
	Vector2D velocity;

	Transform() {
		position.zero();
	}

	Transform(float x, float y) {
		position.x = x;
		position.y = y;
	}

	Transform(float x, float y, int w, int h, int sc) {
		position.x = x;
		position.y = y;
		width = w;
		height = h;
		scale = sc;
	}

	void init() override {
		velocity.zero();
	}

	void update() override {
		position.x += trunc(velocity.x);
		position.y += trunc(velocity.y);
	}

	int getWidth() { return width; }
	int getHeight() { return height; }
	int getScale() { return scale; }

	void setPosition(float x, float y) {
		position.x = x;
		position.y = y;
	}

	static vector<Transform*> colliders;

private:
	int width = 32;
	int height = 32;
	int scale = 1;
};