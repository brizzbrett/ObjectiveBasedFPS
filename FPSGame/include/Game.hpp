#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include "Shader.hpp"
#include "SimpleLogger.hpp"

/*
* @brief returns time since the program began
* @return time
*/
sf::Clock getClock();

/*
* @brief returns a pointer to the game window
* @return pointer to RenderWindow
*/
sf::RenderWindow* getWindow();

/*
* @brief initializes the game from graphics
* @return true if graphics initialize correctly
*/
GLuint GameInit();
#endif