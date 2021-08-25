#include "Game.hpp"
#include "TextureManager.hpp"
#include "SceneManager.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;
SceneManager sceneManager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<Collider*> Game::colliders;
Vector2D Game::mouse;

Entity& player(manager.addEntity());

vector<Entity*>& background(manager.getGroup(Game::Background));
vector<Entity*>& actors(manager.getGroup(Game::Actors));
vector<Entity*>& ui(manager.getGroup(Game::UI));

Game::Game() {

}

Game::~Game() {

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen)
		flags = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		cout << "Subsystems Initialized!..." << endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
			cout << "Window created!" << endl;

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			cout << "Renderer created!" << endl;
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		running = true;
	}
	else
		running = false;

	player.addComponent<Transform>(12 * 32, 10 * 32);
	player.addComponent<PlayerController>();
	player.addComponent<Collider>("player");
	player.addComponent<Sprite>("assets/player.png");
	player.addGroup(Game::Actors);

	sceneManager.loadMenu(manager);
	//sceneManager.loadMap("XML/test.xml", manager, player);
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	case SDL_MOUSEMOTION:
		Game::mouse.x = event.motion.x;
		Game::mouse.y = event.motion.y;
		break;
	default:
		break;
	}
}

void Game::update() {
	preX = player.getComponent<Transform>().position.x;
	preY = player.getComponent<Transform>().position.y;

	manager.refresh();
	manager.update();

	for (Collider* cc : colliders)
		Collision::AABB(player.getComponent<Collider>(), *cc);

	if (player.getComponent<Transform>().position.x > 496 || player.getComponent<Transform>().position.x < 304) {
		float playerTraveled = player.getComponent<Transform>().position.x - preX;

		//cout << playerTraveled << endl;

		player.getComponent<Transform>().position.x -= playerTraveled;

		for (Entity* e : background) {
			e->getComponent<Transform>().position.x -= playerTraveled;
		}
	}
	if (player.getComponent<Transform>().position.y > 416 || player.getComponent<Transform>().position.y < 224) {
		float playerTraveled = player.getComponent<Transform>().position.y - preY;

		//cout << playerTraveled << endl;

		player.getComponent<Transform>().position.y -= playerTraveled;

		for (Entity* e : background) {
			e->getComponent<Transform>().position.y -= playerTraveled;
		}
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	for (Entity* e : background)
		e->draw();
	for (Entity* e : actors)
		e->draw();
	for (Entity* e : ui)
		e->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}

void Game::loadScene(int scene) {
	SDL_Event e;
	switch (scene) {
	case 0:
		e.type = SDL_QUIT;
		SDL_PushEvent(&e);
		break;
	case 1:
		sceneManager.loadMenu(manager);
		break;
	case 2:
		//WARNING: This code is unstable, only allow the last entity in the vector to invoke this
		for (Entity* e : ui)
			e->destroy();
		sceneManager.loadMap("XML/test.xml", manager, player);
		break;
	}
}