#include "SceneManager.hpp"

void SceneManager::loadMenu(Manager& manager) {
	Entity& menuBackground(manager.addEntity());
	menuBackground.addComponent<Transform>(0, 0, 800, 640, 1);
	menuBackground.addComponent<Sprite>("assets/menu-background.png");
	menuBackground.addGroup(Game::UI);

	Entity& quitUI(manager.addEntity());
	quitUI.addComponent<Transform>(17 * 32, 11 * 32, 112, 64, 1);
	quitUI.addComponent<Sprite>("assets/quit.png");
	quitUI.addComponent<SelectUI>("assets/quit.png", "assets/quitselect.png", 0);
	quitUI.addGroup(Game::UI);

	Entity& startUI(manager.addEntity());
	startUI.addComponent<Transform>(17 * 32, 8 * 32, 112, 64, 1);
	startUI.addComponent<Sprite>("assets/start.png");
	startUI.addComponent<SelectUI>("assets/start.png", "assets/startselect.png", 2);
	startUI.addGroup(Game::UI);
}

void SceneManager::loadMap(const char* path, Manager& manager, Entity& player) {
	ifstream file(path);

	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	xml_node<>* root_node = doc.first_node("Script");
	xml_node<>* map_node = root_node->first_node("Map");
	xml_node<>* colliders_node = root_node->first_node("Colliders");

	player.getComponent<Transform>().setPosition(12 * 32, 10 * 32);

	Entity& background(manager.addEntity());
	background.addComponent<Transform>(256, -640, 1800, 1280, 1);
	background.addComponent<Sprite>("assets/bg2.png");
	background.addGroup(Game::Background);

	int maxRows = 0;
	for (xml_node<>* row_node = map_node->first_node("row");
		row_node; row_node = row_node->next_sibling())
		maxRows++;

	int row = 0;
	int col = 0;

	for (xml_node<>* row_node = map_node->first_node("row");
		row_node; row_node = row_node->next_sibling()) {
		stringstream mapTiles = stringstream(row_node->value());

		int tileCode;
		while (mapTiles >> tileCode) {
			Entity& tile(manager.addEntity());
			switch (tileCode) {
			case 1:
				tile.addComponent<Transform>(col * 32, (row - maxRows / 2) * 32);
				tile.addComponent<Sprite>("assets/tiledirt.png");
				tile.addGroup(Game::Background);
				break;
			case 2:
				tile.addComponent<Transform>(col * 32, (row - maxRows / 2) * 32);
				tile.addComponent<Sprite>("assets/tilegrass.png");
				tile.addGroup(Game::Background);
				break;
			case 3:
				tile.addComponent<Transform>(col * 32, (row - maxRows / 2) * 32);
				tile.addComponent<Sprite>("assets/tilerock.png");
				tile.addGroup(Game::Background);
				break;
			default:
				break;
			}
			col++;
		}

		col = 0;
		row++;
	}

	for (xml_node<>* collider_node = colliders_node->first_node("collider");
		collider_node; collider_node = collider_node->next_sibling()) {

		int x = atoi(collider_node->first_node("x")->value()) * 32;
		int y = (atoi(collider_node->first_node("y")->value()) - maxRows / 2) * 32;
		int width = atoi(collider_node->first_node("w")->value()) * 32;
		int height = atoi(collider_node->first_node("h")->value()) * 32;

		Entity& collider(manager.addEntity());
		collider.addComponent<Transform>(x, y, width, height, 1);
		collider.addComponent<Collider>("tile");
		collider.addGroup(Game::Background);
	}
}