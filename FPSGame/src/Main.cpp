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


#define FPS_TIME 0.01666666666f /**<total time per frame in seconds. 60 dps */ 

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock deltaTime; /**<timer that tracks time since last iteration of game loop*/

void GameLoop(Camera* camera, GLuint vbuff, GLuint cbuff, GLuint pid);

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	-4.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  -4.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	-4.597f,  0.770f,  0.761f,
	-4.559f,  0.436f,  0.730f,
	0.359f,  -4.583f,  0.152f,
	0.483f,  -4.596f,  0.789f,
	-4.559f,  0.861f,  0.639f,
	0.195f,  -4.548f,  0.859f,
	0.014f,  0.184f,  -4.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  -4.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  -4.513f,  0.064f,
	0.945f,  0.719f,  -4.592f,
	-4.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  -4.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  -4.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  -4.587f,  0.040f,
	-4.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

/**
* Main application.
*
* @author Brett Aiken
* @param argc The number of command - line arguments provided.
* @param argv An array of command - line argument strings.
*/
int main(int argc, char *argv[])
{
	GLuint programID;
	GLuint vao;
	GLuint vertbuffer;
	GLuint colorbuffer;

	GameInit();

	Camera* camera = new Camera(SCREEN_WIDTH, SCREEN_HEIGHT);

	programID = ShadersInit();

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vertbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	GameLoop(camera, vertbuffer, colorbuffer, programID);

	return 0;
}

/*
* @brief Game loop that handles what happens every frame
*/
void GameLoop(Camera* camera, GLuint vbuff, GLuint cbuff, GLuint pid)
{
	bool running = true;
	getClock().restart();
	deltaTime.restart();

	while (running)
	{
		getWindow()->clear(sf::Color::Black);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera->HandleMovement(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y, deltaTime.getElapsedTime().asSeconds());

		deltaTime.restart();

		glm::mat4 Projection = camera->getProjectionMatrix();
		glm::mat4 View = camera->getViewMatrix();
		glm::mat4 Model = glm::mat4(1.0f);

		GLuint MmatrixID = glGetUniformLocation(pid, "Model");
		glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, &Model[0][0]);

		GLuint VmatrixID = glGetUniformLocation(pid, "View");
		glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, &View[0][0]);

		GLuint PmatrixID = glGetUniformLocation(pid, "Projection");
		glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, &Projection[0][0]);

		glUseProgram(pid);

		// 1st attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vbuff);
		glVertexAttribPointer(
			0,                                // attribute.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);

		// 2nd attribute buffer : colors
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, cbuff);
		glVertexAttribPointer(
			1,                                // attribute. 1 for layout of shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle

		getWindow()->display();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			running = false;
		}
	}
	getWindow()->close();
}