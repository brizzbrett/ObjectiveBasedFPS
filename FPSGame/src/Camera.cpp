#include "Camera.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

Camera::Camera(float theWindowWidth, float theWindowHeight, glm::vec3 cameraPosition)
{	
	position = cameraPosition;
	direction = glm::vec3(1.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

	windowWidth = theWindowWidth;
	windowHeight = theWindowHeight;

	// Calculate the middle of the window
	windowMidPoint = sf::Vector2i(windowWidth / 2, windowHeight / 2);

	projectionMatrix = glm::perspective(glm::radians(90.0f), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.01f, 1000.0f);

	viewMatrix = glm::lookAt(position, position + direction, up);

	speed = 1.0f;

	horizMovement = 3.14f;
	vertMovement = 0;

	pitchSensitivity = 0.002; // How sensitive mouse movements affect looking up and down
	yawSensitivity = 0.002; // How sensitive mouse movements affect looking left and right

	// To begin with, we aren't holding down any keys
	holdingForward = false;
	holdingBackward = false;
	holdingLeftStrafe = false;
	holdingRightStrafe = false;
	
	sf::Mouse::setPosition(windowMidPoint, *getWindow());
}

Camera::~Camera()
{
}

// Function to deal with mouse position changes
void Camera::HandleMouseMove(int mouseX, int mouseY, double deltaTime)
{

	sf::Mouse::setPosition(windowMidPoint, *getWindow());

	horizMovement += yawSensitivity * deltaTime * float(SCREEN_WIDTH / 2 - mouseX);
	vertMovement += pitchSensitivity * deltaTime * float(SCREEN_HEIGHT/ 2 - mouseY);

	std::cout << "Mid window values: " << windowMidPoint.x << "\t" << windowMidPoint.y << std::endl;
	std::cout << "Mouse values     : " << mouseX << "\t" << mouseY << std::endl;
	std::cout << "Horizontal Angle: " << horizMovement << "\t Vertical Angle:" << vertMovement << std::endl << std::endl;
	std::cout << "Camera position: " << position.x << "," << position.y << "," << position.z;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	direction = glm::vec3(
		cos(vertMovement) * sin(horizMovement),
		sin(vertMovement),
		cos(vertMovement) * cos(horizMovement)
	);

	direction = glm::normalize(direction);

	right = glm::vec3(
		sin(horizMovement - 3.14f / 2.0f),
		0,
		cos(vertMovement - 3.14f / 2.0f)
	);

	up = glm::cross(right, direction);
}

// Function to calculate which direction we need to move the camera and by what amount
void Camera::Move(double deltaTime)
{
	// Vector to break up our movement into components along the X, Y and Z axis
	glm::vec3 movement = glm::vec3(0.0f);

	holdingForward = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	holdingBackward = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	holdingLeftStrafe = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	holdingRightStrafe = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (holdingForward)
	{
		slog("Moving forward...");
		position += speed * direction;
	}

	if (holdingBackward)
	{
		slog("Moving backward...");
		position -= speed * direction;
	}

	if (holdingLeftStrafe)
	{
		slog("Strafing left...");
		position -= speed/10 * right;
	}

	if (holdingRightStrafe)
	{
		slog("Strafing right...");
		position += speed/10 * right;
	}
}

void Camera::HandleMovement(int mouseX, int mouseY, double deltaTime) 
{
	this->HandleMouseMove(mouseX, mouseY, deltaTime);
	this->Move(deltaTime);

	setViewMatrix(glm::lookAt(this->getPosition(), 
							  this->getPosition() + this->getDirection(), 
							  this->getUp()
							  )
	);
}