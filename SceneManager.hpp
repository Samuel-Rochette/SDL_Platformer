#pragma once

#include "Game.hpp"
#include "Components.hpp"
#include "ECS.hpp"
#include "rapidxml.hpp"
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace rapidxml;

class SceneManager {
public:
	static void loadMenu(Manager& manager);
	static void loadMap(const char* path, Manager& manager, Entity& player);
};