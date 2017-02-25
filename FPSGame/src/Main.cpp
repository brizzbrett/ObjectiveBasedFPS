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

/*
* @brief Game loop that handles what happens every frame
*/
void GameLoop(bool running, Camera* camera, Entity* ent, Terrain* terr);

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
	GLuint vao;

	ResourceManager* resourceManager;
	Camera* camera;
	Entity* entity;

	Terrain* terrain;



	game = GameInit();

	resourceManager = &ResourceManager::getResourceManager();

	entity = new Entity(resourceManager->getVertexBufferArray()->at(0),
						resourceManager->getVertexBufferArray()->at(1),
						glm::vec3(0.0f, 0.0f, 0.0f)
	);

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 100.0f));

	terrain = new Terrain();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	terrain->LoadTexture2D("terrain.jpg");

	GameLoop(game, camera, entity, terrain);


	return 0;
}

void GameLoop(bool running, Camera* camera, Entity* ent, Terrain* terr)
{
	getClock().restart();
	deltaTime.restart();

	while (running)
	{
		getWindow()->clear(sf::Color::Black);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->HandleMovement(sf::Mouse::getPosition(*getWindow()).x, sf::Mouse::getPosition(*getWindow()).y, deltaTime.getElapsedTime().asSeconds());
		deltaTime.restart();

		glm::mat4 Projection = camera->getProjectionMatrix();
		glm::mat4 View = camera->getViewMatrix();
		glm::mat4 Model = glm::mat4(1.0f);

		GLuint PmatrixID = glGetUniformLocation(ent->getVertexBuffer()->getShader()->getProgram(), "Projection");
		glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, &Projection[0][0]);		

		GLuint VmatrixID = glGetUniformLocation(ent->getVertexBuffer()->getShader()->getProgram(), "View");
		glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, &View[0][0]);		

		GLuint MmatrixID = glGetUniformLocation(ent->getVertexBuffer()->getShader()->getProgram(), "Model");
		glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, &Model[0][0]);

		glUseProgram(ent->getVertexBuffer()->getShader()->getProgram());

		// 1st attribute buffer : vertices
		ent->getVertexBuffer()->configureVertexAttributes();

		// 2nd attribute buffer : colors
		ent->getColorBuffer()->configureVertexAttributes();

		terr->Render();

		//Draw Arrays
		ent->getVertexBuffer()->renderVertexBuffer();
		ent->getColorBuffer()->renderVertexBuffer();

		getWindow()->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			running = false;
		}
	}
	getWindow()->close();
}