#include "Camera.hpp"

const double Camera::TO_RADS = 3.141592654 / 180.0; // The value of 1 degree in radians

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

Camera::Camera(float theWindowWidth, float theWindowHeight)
{
	InitCamera();

	windowWidth = theWindowWidth;
	windowHeight = theWindowHeight;

	// Calculate the middle of the window
	windowMidPoint = sf::Vector2i(windowWidth / 2, windowHeight / 2);

	sf::Mouse::setPosition(windowMidPoint, *getWindow());
}

Camera::~Camera()
{
	// Nothing to do here - we don't need to free memory as all member variables
	// were declared on the stack.
}

void Camera::InitCamera()
{
	// Set position, rotation and speed values to zero
	position = glm::vec3(0.0f,0.0f,0.0f);
	rotation = glm::vec3(0.0f);
	speed = glm::vec3(0.0f);

	// How fast we move (higher values mean we move and strafe faster)
	movementSpeedFactor = 5.0f;

	pitchSensitivity = 0.2; // How sensitive mouse movements affect looking up and down
	yawSensitivity = 0.2; // How sensitive mouse movements affect looking left and right

	// To begin with, we aren't holding down any keys
	holdingForward = false;
	holdingBackward = false;
	holdingLeftStrafe = false;
	holdingRightStrafe = false;
}

// Function to convert degrees to radians
const double Camera::toRads(const double &theAngleInDegrees) const
{
	return theAngleInDegrees * TO_RADS;
}

// Function to deal with mouse position changes
void Camera::HandleMouseMove(int mouseX, int mouseY, double deltaTime)
{
	// Calculate our horizontal and vertical mouse movement from middle of the window
	float horizMovement = 0;
	float vertMovement = 0;

	horizMovement += yawSensitivity * deltaTime * float(SCREEN_WIDTH / 2 - mouseX);
	vertMovement += pitchSensitivity * deltaTime * float(SCREEN_HEIGHT / 2 - mouseY);

	std::cout << "Mid window values: " << windowMidPoint.x << "\t" << windowMidPoint.y << std::endl;
	std::cout << "Mouse values     : " << mouseX << "\t" << mouseY << std::endl;
	std::cout << horizMovement << "\t" << vertMovement << std::endl << std::endl;

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	rotation = glm::vec3(
		cos(vertMovement) * sin(horizMovement),
		sin(vertMovement),
		cos(vertMovement) * cos(horizMovement)
	);

	right = glm::vec3(
		sin(horizMovement - 3.14f / 2.0f),
		0,
		cos(vertMovement - 3.14f / 2.0f)
	);

	up = glm::cross(right, rotation);

	// Reset the mouse position to the centre of the window each frame
	//sf::Mouse::setPosition(windowMidPoint, *getWindow());
}

// Function to calculate which direction we need to move the camera and by what amount
void Camera::Move(double deltaTime)
{
	// Vector to break up our movement into components along the X, Y and Z axis
	glm::vec3 movement;

	// Get the sine and cosine of our X and Y axis rotation
	double sinXRot = sin(toRads(rotation.x));
	double cosXRot = cos(toRads(rotation.x));

	double sinYRot = sin(toRads(rotation.y));
	double cosYRot = cos(toRads(rotation.y));

	double pitchLimitFactor = cosXRot; // This cancels out moving on the Z axis when we're looking up or down

	holdingForward = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
	holdingBackward = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
	holdingLeftStrafe = sf::Keyboard::isKeyPressed(sf::Keyboard::A);
	holdingRightStrafe = sf::Keyboard::isKeyPressed(sf::Keyboard::D);

	if (holdingForward)
	{
		slog("Moving forward...");
		movement += rotation;
	}

	if (holdingBackward)
	{
		slog("Moving backward...");
		movement -= rotation;
	}

	if (holdingLeftStrafe)
	{
		slog("Strafing left...");
		movement -= right;
	}

	if (holdingRightStrafe)
	{
		slog("Strafing right...");
		movement += right;
	}

	// Normalise our movement vector
	if (movement != glm::vec3(0.0f))
	{
		movement = glm::normalize(movement);
	}

	// Calculate our value to keep the movement the same speed regardless of the framerate...
	double framerateIndependentFactor = movementSpeedFactor * deltaTime;

	// .. and then apply it to our movement vector.
	movement *= framerateIndependentFactor;

	// Finally, apply the movement to our position
	position += movement;
}

void Camera::HandleMovement(int mouseX, int mouseY, double deltaTime) 
{
	this->HandleMouseMove(mouseX, mouseY, deltaTime);
	this->Move(deltaTime);
}