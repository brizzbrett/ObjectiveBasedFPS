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
#include "VertexBuffer.hpp"
#include "ResourceManager.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock deltaTime; /**<timer that tracks time since last iteration of game loop*/

void GameLoop(bool running, Camera* camera, VertexBuffer* vbuff, VertexBuffer* cbuff, GLuint pid);

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

	game = GameInit();

	resourceManager = &ResourceManager::getResourceManager();

	camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT, glm::vec3(0.0f, 0.0f, 100.0f));

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GameLoop(game, 
			camera, 
			resourceManager->getVertexBufferArray()->at(0), 
			resourceManager->getVertexBufferArray()->at(1), 
			resourceManager->getShaderArray()->at(0)->getProgram()
	);

	return 0;
}

/*
* @brief Game loop that handles what happens every frame
*/
void GameLoop(bool running, Camera* camera, VertexBuffer* vbuff, VertexBuffer* cbuff, GLuint pid)
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

		GLuint PmatrixID = glGetUniformLocation(pid, "Projection");
		glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, &Projection[0][0]);		

		GLuint VmatrixID = glGetUniformLocation(pid, "View");
		glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, &View[0][0]);		

		GLuint MmatrixID = glGetUniformLocation(pid, "Model");
		glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, &Model[0][0]);

		// 1st attribute buffer : vertices
		vbuff->configureVertexAttributes(0);

		// 2nd attribute buffer : colors
		cbuff->configureVertexAttributes(1);

		//Draw Arrays
		vbuff->renderVertexBuffer();
		cbuff->renderVertexBuffer();

		getWindow()->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			running = false;
		}
	}
	getWindow()->close();
}