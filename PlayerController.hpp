#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class PlayerController : public Component {
public:
	Transform* transform;
	Sprite* sprite;
	bool grounded = true;
	bool lwallstate = false;
	bool rwallstate = false;
	float fallSpeed = 12;
	float gravity = 1;
	float moveSpeed = 8;

	void init() override {
		transform = &entity->getComponent<Transform>();
		sprite = &entity->getComponent<Sprite>();
		transform->velocity.y = fallSpeed;
	}

	void update() override {

		if (!(lwallstate || rwallstate)) {
			fallSpeed = 12;
			gravity = 1;
		}
		else {
			fallSpeed = 2;
			gravity = 2;
		}

		transform->velocity.y += gravity;
		if (transform->velocity.y > fallSpeed)
			transform->velocity.y = fallSpeed;

		if (grounded)
			sprite->playAnimation("idle");
		else
			sprite->playAnimation("jump");

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_A] && grounded) {
			sprite->playAnimation("run");
			sprite->flip = SDL_FLIP_NONE;
			transform->velocity.x -= 1;
			if (transform->velocity.x < moveSpeed * -1)
				transform->velocity.x = moveSpeed * -1;
		}
		else if (state[SDL_SCANCODE_D] && grounded) {
			sprite->playAnimation("run");
			sprite->flip = SDL_FLIP_HORIZONTAL;
			transform->velocity.x += 1;
			if (transform->velocity.x > moveSpeed)
				transform->velocity.x = moveSpeed;
		}
		else if (!state[SDL_SCANCODE_A] && transform->velocity.x < 0 && grounded) {
			transform->velocity.x += 1;
			if (transform->velocity.x > 0)
				transform->velocity.x = 0;
		}
		else if (!state[SDL_SCANCODE_D] && transform->velocity.x > 0 && grounded) {
			transform->velocity.x -= 1;
			if (transform->velocity.x < 0)
				transform->velocity.x = 0;
		}
		else if (state[SDL_SCANCODE_A] && !grounded && transform->velocity.x > moveSpeed * -1)
			transform->velocity.x -= 0.2;
		else if (state[SDL_SCANCODE_D] && !grounded && transform->velocity.x < moveSpeed)
			transform->velocity.x += 0.2;

		if (Game::event.type == SDL_KEYDOWN) {
			SDL_Keycode eventCode = Game::event.key.keysym.sym;

			if (eventCode == SDLK_SPACE && grounded)
				transform->velocity.y = -16;
			else if (eventCode == SDLK_SPACE && rwallstate) {
				rwallstate = false;
				transform->velocity.y = -12;
				transform->velocity.x = -4;
			}
			else if (eventCode == SDLK_SPACE && lwallstate) {
				lwallstate = false;
				transform->velocity.y = -12;
				transform->velocity.x = 4;
			}

			if ((eventCode == SDLK_a || eventCode == SDLK_d) && (lwallstate || rwallstate)) {
				lwallstate = false;
				rwallstate = false;
				transform->velocity.x = 0;
			}
		}

		//cout << "(" << transform->position.x << ", " << transform->position.y << ")" << endl;
		cout << "velocity: (" << transform->velocity.x << ", " << transform->velocity.y << ")" << endl;

		grounded = false;
		lwallstate = false;
		rwallstate = false;

	}
};