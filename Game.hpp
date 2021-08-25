#ifndef Game_hpp
#define Game_hpp

#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>

class Collider;

using namespace std;

class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	
	void handleEvents();
	void update();
	void render();
	void clean();

	bool isRunning() { return running; }

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static vector<Collider*> colliders;

	enum groupLabels : size_t {
		Background,
		Actors
	};

private:
	int cnt = 0;
	bool running;
	SDL_Window* window;
};

#endif