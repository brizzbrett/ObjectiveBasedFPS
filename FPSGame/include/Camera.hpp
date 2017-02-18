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
	// Camera position
	glm::vec3 position;

	// Camera rotation
	glm::vec3 rotation;

	// Camera right
	glm::vec3 right;

	// Camera up
	glm::vec3 up;

	// Camera movement speed. When we call the move() function on a camera, it moves using these speeds
	glm::vec3 speed;

	double movementSpeedFactor; // Controls how fast the camera moves
	double pitchSensitivity;    // Controls how sensitive mouse movements affect looking up and down
	double yawSensitivity;      // Controls how sensitive mouse movements affect looking left and right

								// Window size in pixels and where the midpoint of it falls
	int windowWidth;
	int windowHeight;
	sf::Vector2i windowMidPoint;

	// Method to set some reasonable default values. For internal use by the class only.
	void InitCamera();

	// Mouse movement handler to look around
	void HandleMouseMove(int mouseX, int mouseY, double deltaTime);

	// Method to move the camera based on the current direction
	void Move(double deltaTime);
public:

	static const double TO_RADS; // The value of 1 degree in radians

								 // Holding any keys down?
	bool holdingForward;
	bool holdingBackward;
	bool holdingLeftStrafe;
	bool holdingRightStrafe;

	// Constructor
	Camera(float windowWidth, float windowHeight);

	// Destructor
	~Camera();

	// movement handler to look around and move the camera FPS style
	void HandleMovement(int mouseX, int mouseY, double deltaTime);

	// Method to convert an angle in degress to radians
	const double toRads(const double &angleInDegrees) const;



	// --------------------------------- Inline methods ----------------------------------------------

	// Setters to allow for change of vertical (pitch) and horizontal (yaw) mouse movement sensitivity
	float getPitchSensitivity() { return pitchSensitivity; }
	void  setPitchSensitivity(float value) { pitchSensitivity = value; }
	float getYawSensitivity() { return yawSensitivity; }
	void  setYawSensitivity(float value) { yawSensitivity = value; }

	// Position getters
	glm::vec3 getPosition() const { return position; }
	double getXPos()           const { return position.x; }
	double getYPos()           const { return position.y; }
	double getZPos()           const { return position.z; }

	// Rotation getters
	glm::vec3 getRotation() const { return rotation; }
	double getXRot()           const { return rotation.x; }
	double getYRot()           const { return rotation.y; }
	double getZRot()           const { return rotation.z; }

	// Right getters
	glm::vec3 getRight() const { return right; }
	double getXRight()           const { return right.x; }
	double getYRight()           const { return right.y; }
	double getZRight()           const { return right.z; }

	// Up getters
	glm::vec3 getUp() const { return up; }
	double getXUp()           const { return up.x; }
	double getYUp()           const { return up.y; }
	double getZUp()           const { return up.z; }
};

#endif // CAMERA_H