/**
* @file src\main.cpp
*
* Implements the main class.
*/

#include "game.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"
#include "Player.hpp"
#include "Terrain.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

/**
* Main application.
*
* @author Brett Aiken
* @param argc The number of command - line arguments provided.
* @param argv An array of command - line argument strings.
*/
int main(int argc, char *argv[])
{

	GLuint game = GameInit();
	ResourceManager* resourceManager = &ResourceManager::getResourceManager();
	Player* player = (Player*)resourceManager->getEntityList()->at(0);

	float height = resourceManager->getTerrainList()->at(0).GetHeight(0.0f, 0.0f);
	float offset = 1.75f;

	player->camera.Look(glm::vec3(0.0f, height + offset, 0.0f), glm::vec3(0.0f, height + offset, -1.0f));

	getClock().restart();

	while (game)
	{

		getWindow()->clear(sf::Color::Transparent);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		resourceManager->UpdateAll();
		resourceManager->DrawAll();

		//slog("%f,%f", player->getPosition().x, player->getPosition().y);

		getWindow()->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game = false;
		}
	}
	getWindow()->close();

	return 0;
}