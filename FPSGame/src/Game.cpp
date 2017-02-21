#include "Game.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock totalClock;/**<tracks total time since ininitation of gamescene*/

static sf::RenderWindow* window; /**<the window to render to*/


/*
* @brief returns time since the program began
* @return time
*/
sf::Clock getClock()
{
	return totalClock;
}

/*
* @brief returns a pointer to the game window
* @return pointer to RenderWindow
*/
sf::RenderWindow* getWindow()
{
	return window;
}

/*
* @brief initializes the game from graphics to loading scene
*/
void GameInit()
{
	GraphicsInit();
}

/*
* @brief Initializes sfml window and glew
*/
void GraphicsInit()
{
	int err;
	sf::ContextSettings settings;
	GLuint vert_buff, uv_buff;

	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = .0;

	//Create context
	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "FPS Game", sf::Style::Default, settings);

	window->setVerticalSyncEnabled(true);

	if ((err = glewInit()) != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
		exit(1);
	}
	// Enable depth test
	glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);
}