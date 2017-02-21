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
	glm::vec3 position;

	glm::vec3 direction;

	glm::vec3 right;

	glm::vec3 up;

	float speed;

	float horizMovement;
	float vertMovement;

	float pitchSensitivity; 
	float yawSensitivity;  

	int windowWidth;
	int windowHeight;
	sf::Vector2i windowMidPoint;

	glm::mat4 projectionMatrix, viewMatrix;

	void HandleMouseMove(int mouseX, int mouseY, double deltaTime);

	void Move(double deltaTime);
public:

	bool holdingForward;
	bool holdingBackward;
	bool holdingLeftStrafe;
	bool holdingRightStrafe;

	Camera(float windowWidth, float windowHeight, glm::vec3 cameraPosition = glm::vec3(0.0f,0.0f,0.0f));

	~Camera();

	void HandleMovement(int mouseX, int mouseY, double deltaTime);

	float getPitchSensitivity() { return pitchSensitivity; }
	void  setPitchSensitivity(float value) { pitchSensitivity = value; }
	float getYawSensitivity() { return yawSensitivity; }
	void  setYawSensitivity(float value) { yawSensitivity = value; }

	glm::mat4 getProjectionMatrix() { return projectionMatrix; }
	void setProjectionMatrix(glm::mat4 value) { projectionMatrix = value; }
	glm::mat4 getViewMatrix() { return viewMatrix; }
	void setViewMatrix(glm::mat4 value) { viewMatrix = value; }

	glm::vec3 getPosition() const { return position; }
	double getXPos()           const { return position.x; }
	double getYPos()           const { return position.y; }
	double getZPos()           const { return position.z; }

	glm::vec3 getDirection() const { return direction; }
	double getXDir()           const { return direction.x; }
	double getYDir()           const { return direction.y; }
	double getZDir()           const { return direction.z; }

	glm::vec3 getRight() const { return right; }
	double getXRight()           const { return right.x; }
	double getYRight()           const { return right.y; }
	double getZRight()           const { return right.z; }

	glm::vec3 getUp() const { return up; }
	double getXUp()           const { return up.x; }
	double getYUp()           const { return up.y; }
	double getZUp()           const { return up.z; }
};

#endif 