/**
* @file src\main.cpp
*
* Implements the main class.
*/
#ifndef _DEBUG
#include <windows.hpp>
#endif
#include "game.hpp"
#include "Camera.hpp"
#include "ResourceManager.hpp"
#include "Entity.hpp"
#include "Terrain.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock deltaTime; /**<timer that tracks time since last iteration of game loop*/

/**
* Main application.
*
* @author Brett Aiken
* @param argc The number of command - line arguments provided.
* @param argv An array of command - line argument strings.
*/
int main(int argc, char *argv[])
{
	GLuint game;
	ResourceManager* resourceManager;

	game = GameInit();

	resourceManager = &ResourceManager::getResourceManager();

	resourceManager->camera.SetPerspective(90.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.125f, 1024.0f);

	float height = resourceManager->getTerrainList()->at(0).GetHeight(0.0f, 0.0f);
	float offset = 1.75f;

	resourceManager->camera.Look(glm::vec3(0.0f, height + offset, 0.0f), glm::vec3(0.0f, height + offset, -1.0f));

	getClock().restart();
	deltaTime.restart();

	while (game)
	{

		resourceManager->Update(deltaTime.getElapsedTime().asSeconds());
		deltaTime.restart();

		getWindow()->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			game = false;
		}
	}
	getWindow()->close();

	return 0;
}