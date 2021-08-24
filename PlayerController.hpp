#pragma once

#include "Game.hpp"
#include "ECS.hpp"
#include "Components.hpp"

class PlayerController : public Component {
public:
	Transform* transform;
	bool grounded = true;
	bool lwallstate = false;
	bool rwallstate = false;
	float fallSpeed = 6;
	float gravity = 0.5;
	float moveSpeed = 4;

	void init() override {
		transform = &entity->getComponent<Transform>();
		transform->velocity.y = fallSpeed;
	}

	void update() override {

		if (!(lwallstate || rwallstate)) {
			fallSpeed = 6;
			gravity = 0.5;
		}
		else {
			fallSpeed = 1;
			gravity = 1;
		}

		transform->velocity.y += gravity;
		if (transform->velocity.y > fallSpeed)
			transform->velocity.y = fallSpeed;

		const Uint8 *state = SDL_GetKeyboardState(NULL);

		if (state[SDL_SCANCODE_A] && grounded && transform->velocity.x > moveSpeed * -1) {
			transform->velocity.x -= 0.5;
			if (transform->velocity.x < moveSpeed * -1)
				transform->velocity.x = moveSpeed * -1;
		}
		else if (state[SDL_SCANCODE_D] && grounded && transform->velocity.x < moveSpeed) {
			transform->velocity.x += 0.5;
			if (transform->velocity.x > moveSpeed)
				transform->velocity.x = moveSpeed;
		}
		else if (!state[SDL_SCANCODE_A] && transform->velocity.x < 0 && grounded) {
			transform->velocity.x += 0.5;
			if (transform->velocity.x > 0)
				transform->velocity.x = 0;
		}
		else if (!state[SDL_SCANCODE_D] && transform->velocity.x > 0 && grounded) {
			transform->velocity.x -= 0.5;
			if (transform->velocity.x < 0)
				transform->velocity.x = 0;
		}
		else if (state[SDL_SCANCODE_A] && !grounded && transform->velocity.x > moveSpeed * -1)
			transform->velocity.x -= 0.1;
		else if (state[SDL_SCANCODE_D] && !grounded && transform->velocity.x < moveSpeed)
			transform->velocity.x += 0.1;

		if (Game::event.type == SDL_KEYDOWN) {
			SDL_Keycode eventCode = Game::event.key.keysym.sym;

			if (eventCode == SDLK_SPACE && grounded)
				transform->velocity.y = -8;
			else if (eventCode == SDLK_SPACE && rwallstate) {
				rwallstate = false;
				transform->velocity.y = -6;
				transform->velocity.x = -2;
			}
			else if (eventCode == SDLK_SPACE && lwallstate) {
				lwallstate = false;
				transform->velocity.y = -6;
				transform->velocity.x = 2;
			}

			if ((eventCode == SDLK_a || eventCode == SDLK_d) && (lwallstate || rwallstate)) {
				lwallstate = false;
				rwallstate = false;
				transform->velocity.x = 0;
			}
		}

		cout << "velocity: (" << transform->velocity.x << ", " << transform->velocity.y << ")" << endl;

		grounded = false;
		lwallstate = false;
		rwallstate = false;

	}
};