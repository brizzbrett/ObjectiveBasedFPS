#include "Game.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock totalClock;/**<tracks total time since ininitation of gamescene*/

static sf::RenderWindow* window; /**<the window to render to*/

/*
* @brief Initializes sfml window and glew
* @return true if successful initialization
*/
GLuint GraphicsInit();


sf::Clock getClock()
{
	return totalClock;
}

sf::RenderWindow* getWindow()
{
	return window;
}

GLuint GameInit()
{
	return GraphicsInit();
}

GLuint GraphicsInit()
{
	int err;
	sf::ContextSettings settings;
	GLuint vert_buff, uv_buff;

	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 4;
	settings.minorVersion = .0;

	window = new sf::RenderWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "FPS Game", sf::Style::Default, settings);

	window->setVerticalSyncEnabled(true);

	if ((err = glewInit()) != GLEW_OK)
	{
		printf("Error: %s\n", glewGetErrorString(err));
		return 0;
		exit(1);
	}

	if (!GLEW_EXT_framebuffer_object)
	{
		slog("GLEW FBO not set");
		exit(0);
	}

	glEnable(GL_DEPTH_TEST | GL_CULL_FACE);

	glDepthFunc(GL_LESS);

	return 1;
}