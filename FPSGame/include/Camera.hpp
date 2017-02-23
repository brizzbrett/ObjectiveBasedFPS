#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>// Used only for sin() and cos() functions
#include <glew.h>
#include <glm/glm.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Game.hpp"

class Camera
{
protected:

	glm::vec3 position; /**<camera's relative position */
	glm::vec3 direction; /**<direction the camera is facing */
	glm::vec3 right; /**<the right vector, used to find up vector using cross product */
	glm::vec3 up; /**< the up vector*/

	float speed; /**< speed at which the camera moves front and back, side to side*/

	float horizMovement; /**<The angle of horizontal movement */
	float vertMovement; /**<The angle of vertical movement */

	float pitchSensitivity; /**<speed of the rotation when rotating along the x coordinate */
	float yawSensitivity; /**<speed of the rotation when rotaing along the y coordinate */

	int windowWidth; /**<width of the game window */
	int windowHeight; /**<height of the game window */
	sf::Vector2i windowMidPoint; /**<midpoint of the game window in pixels */

	glm::mat4 projectionMatrix, viewMatrix; /**<the projection matrix and view matrix */
	
	/*
	* @brief Handles what happens to the camera when you move the mouse
	* @param mouseX the x position of the mouse
	* @param mouseY the y position of the mouse
	* @param deltaTime the time that's passed since last frame
	*/
	void HandleMouseMove(int mouseX, int mouseY, double deltaTime);

	/*
	* @brief Handles what happens to the camera when you press the keys (W,A,S,D).
	* @param deltaTime the time that's passed since last frame
	*/
	void Move(double deltaTime);

public:

	bool holdingForward; /**<true if pressing down W */
	bool holdingBackward; /**<true if pressing down S */
	bool holdingLeftStrafe; /**<true if pressing down A */
	bool holdingRightStrafe; /**<true if pression down D */

	/*
	* @brief Camera constructor. Overloaded to take 2 floats and a glm::vec3 if necessary
	* @param windowWidth the width of the window
	* @param windowHeight the height of the window
	* @param (optional)cameraPosition the starting position of the camera. (Default: (0,0,0))
	*/
	Camera(float windowWidth, float windowHeight, glm::vec3 cameraPosition = glm::vec3(0.0f,0.0f,0.0f));

	/*
	* @brief Camera destructor.
	*/
	~Camera();

	/*
	* @brief Handles camera movement.
	* @param mouseX the x position of the mouse
	* @param mouseY the y position of the mouse
	* @param deltaTime the time that's passed since last frame
	*/
	void HandleMovement(int mouseX, int mouseY, double deltaTime);

	/*
	* @brief Getter: the pitch sensitivity
	* @return pitchSensitivity
	*/
	float getPitchSensitivity() { return pitchSensitivity; }

	/*
	* @brief Setter: the pitch sensitivity
	* @param value pitchSensitivity's new value
	*/
	void  setPitchSensitivity(float value) { pitchSensitivity = value; }

	/*
	* @brief Getter: the yaw sensitivity
	* @return yawSensitivity
	*/
	float getYawSensitivity() { return yawSensitivity; }

	/*
	* @brief Setter: the yaw sensitivity
	* @param value yawSensitivity's new value
	*/
	void  setYawSensitivity(float value) { yawSensitivity = value; }

	/*
	* @brief Getter: the projection matrix
	* @return projectionMatrix
	*/
	glm::mat4 getProjectionMatrix() { return projectionMatrix; }

	/*
	* @brief Setter: the projection matrix
	* @param value projectionMatrix's new value
	*/
	void setProjectionMatrix(glm::mat4 value) { projectionMatrix = value; }

	/*
	* @brief Getter: the viewMatrix
	* @return viewMatrix
	*/
	glm::mat4 getViewMatrix() { return viewMatrix; }

	/*
	* @brief Setter: the view matrix
	* @param value viewMatrix's new value
	*/
	void setViewMatrix(glm::mat4 value) { viewMatrix = value; }

	/*
	* @brief Getter: the camera position
	* @return position
	*/
	glm::vec3 getPosition() const { return position; }

	/*
	* @brief Getter: the camera direction
	* @return direction
	*/
	glm::vec3 getDirection() const { return direction; }

	/*
	* @brief Getter: the right vector
	* @return right
	*/
	glm::vec3 getRight() const { return right; }

	/*
	* @brief Getter: the up vector
	* @return up
	*/
	glm::vec3 getUp() const { return up; }
};

#endif 