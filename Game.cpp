#include "Game.hpp"
#include "TextureManager.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<Collider*> Game::colliders;

Entity& player(manager.addEntity());
Entity& wall(manager.addEntity());

Entity& tile0(manager.addEntity());
Entity& tile1(manager.addEntity());
Entity& tile2(manager.addEntity());

vector<Entity*>& background(manager.getGroup(Game::Background));
vector<Entity*>& actors(manager.getGroup(Game::Actors));

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

	int lvl[20][25] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,2,2,2,2,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,2},
		{2,0,0,0,0,0,0,0,0,0,0,0,0,0,2,1,1,1,2,0,0,0,0,0,2},
		{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,2,2,2,2,2,2,2},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};

	int type = 0;
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 25; j++) {
			type = lvl[i][j];
			switch (type) {
			case 0:
				generateMapTile(i, j, "assets/background.png");
				break;
			case 1:
				generateMapTile(i, j, "assets/floor.png");
				break;
			case 2:
				generateMapTile(i, j, "assets/floor.png");
				break;
			default:
				break;
			}
		}
	}

	generateCollider(0, 14 * 32, 25 * 32, 6 * 32);
	generateCollider(0, 5 * 32, 32, 10 * 32);
	generateCollider(24 * 32, 5 * 32, 32, 10 * 32);
	generateCollider(14 * 32, 10 * 32, 5 * 32, 6 * 32);
	generateCollider(16 * 32, 6 * 32, 3 * 32, 32);

	//tile0.addComponent<Tile>(150, 320, 32, 32, 0);
	//tile1.addComponent<Tile>(200, 320, 32, 32, 1);
	//tile1.addComponent<Collider>("tile1");
	//tile2.addComponent<Tile>(0, 320, 32, 32, 1);
	//tile2.addComponent<Collider>("tile2");
	//tile0.addGroup(Background);
	//tile1.addGroup(Background);
	//tile2.addGroup(Background);

	player.addComponent<Transform>(64, 320);
	player.addComponent<PlayerController>();
	player.addComponent<Collider>("player");
	player.addComponent<Sprite>("assets/player.png");
	player.addGroup(Actors);

	//wall.addComponent<Transform>(300, 300, 20, 300, 1);
	//wall.addComponent<Sprite>("assets/dirt.png");
	//wall.addComponent<Collider>("wall");
	//wall.addGroup(Background);
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		running = false;
		break;
	default:
		break;
	}
}

void Game::update() {
	manager.refresh();
	manager.update();

	for (Collider* cc : colliders)
		Collision::AABB(player.getComponent<Collider>(), *cc);
}

void Game::render() {
	SDL_RenderClear(renderer);
	
	for (Entity* e : background)
		e->draw();
	for (Entity* e : actors)
		e->draw();

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game Cleaned" << endl;
}

void Game::generateMapTile(int y, int x, const char* path) {
	Entity& tile(manager.addEntity());
	tile.addComponent<Transform>(32 * x, 32 * y);
	tile.addComponent<Sprite>(path);
	tile.addGroup(Background);
}

void Game::generateCollider(int x, int y, int w, int h) {
	Entity& collider(manager.addEntity());
	collider.addComponent<Transform>(x, y, w, h, 1);
	collider.addComponent<Collider>("tile");
	collider.addGroup(Background);
}