#include "SceneManager.hpp"

void SceneManager::loadMap(const char* path, Manager& manager, Entity& player) {
	ifstream file(path);

	vector<char> buffer((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
	buffer.push_back('\0');

	xml_document<> doc;
	doc.parse<0>(&buffer[0]);

	xml_node<>* root_node = doc.first_node("Script");
	xml_node<>* map_node = root_node->first_node("Map");
	xml_node<>* colliders_node = root_node->first_node("Colliders");
	xml_node<>* player_node = root_node->first_node("Player");

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
				tile.addComponent<Transform>(32 * col, 32 * row);
				tile.addComponent<Sprite>("assets/floor.png");
				tile.addGroup(Game::Background);
				break;
			default:
				tile.addComponent<Transform>(32 * col, 32 * row);
				tile.addComponent<Sprite>("assets/background.png");
				tile.addGroup(Game::Background);
				break;
			}
			col++;
		}

		col = 0;
		row++;
	}

	for (xml_node<>* collider_node = colliders_node->first_node("collider");
		collider_node; collider_node = collider_node->next_sibling()) {

		int xpos = atoi(collider_node->first_node("x")->value()) * 32;
		int ypos = atoi(collider_node->first_node("y")->value()) * 32;
		int width = atoi(collider_node->first_node("w")->value()) * 32;
		int height = atoi(collider_node->first_node("h")->value()) * 32;

		Entity& collider(manager.addEntity());
		collider.addComponent<Transform>(xpos, ypos, width, height, 1);
		collider.addComponent<Collider>("tile");
		collider.addGroup(Game::Background);
	}

	int xpos = atoi(player_node->first_node("x")->value()) * 32;
	int ypos = atoi(player_node->first_node("y")->value()) * 32;

	player.getComponent<Transform>().setPosition(xpos, ypos);
}