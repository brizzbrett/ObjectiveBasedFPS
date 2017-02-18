#pragma once
#ifndef _GAME_H_
#define _GAME_H_

#include <glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

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
* @brief initializes the game from graphics to loading scene and managing client connection
*/
void GameInit();

/*
* @brief Initializes sfml window and glew
*/
void GraphicsInit();
#endif