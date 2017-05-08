#include "Camera.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

Camera::Camera()
{
	mousex = 0;
	mousey = 0;

	x = glm::vec3(1.0f, 0.0f, 0.0f);
	y = glm::vec3(0.0f, 1.0f, 0.0f);
	z = glm::vec3(0.0f, 0.0f, 1.0f);

	pos = glm::vec3(0.0f, 0.0f, 5.0f);
	ref = glm::vec3(0.0f, 0.0f, 0.0f);

	SetView();
}

Camera::~Camera()
{
}

void Camera::Look(const glm::vec3 &pos, const glm::vec3 &ref, bool rotAroundRef)
{
	this->pos = pos;
	this->ref = ref;

	z = glm::normalize(pos - ref);

	if (z.y == -1.0f)
	{
		x = glm::vec3(1.0f, 0.0f, 0.0f);
		y = glm::vec3(0.0f, 0.0f, 1.0f);
	}
	else if (z.y > -1.0f && z.y < 0.0f)
	{
		x = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), z);
		y = glm::cross(z, x);
	}
	else if (z.y == 0.0f)
	{
		y = glm::vec3(0.0f, 1.0f, 0.0f);
		x = glm::cross(y, z);
	}
	else if (z.y > 0.0f && z.y < 1.0f)
	{
		x = glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), z);
		y = glm::cross(z, x);
	}
	else if (z.y == 1.0f)
	{
		x = glm::vec3(1.0f, 0.0f, 0.0f);
		y = glm::vec3(0.0f, 0.0f, -1.0f);
	}

	if (!rotAroundRef)
	{
		this->ref = this->pos - z * 0.05f;
	}

	SetView();
}

void Camera::Move(const glm::vec3 &movement)
{
	pos += movement;
	ref += movement;

	SetView();
}

glm::vec3 Camera::KeyMove(float dt)
{
	float Speed = 20.0f;

	float Distance = Speed * dt;

	up = glm::vec3(0.0f, 1.0f, 0.0f);
	right = x;
	forward = glm::cross(up, right);

	up *= Distance;
	right *= Distance;
	forward *= Distance;

	glm::vec3 movement;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
	{ 
		movement += forward; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
	{ 
		movement -= forward; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
	{ 
		movement -= right; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
	{ 
		movement += right; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
	{ 
		movement += up; 
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
	{ 
		movement -= up; 
	}

	return movement;
}

glm::mat4 rotate(float angle, const glm::vec3 &u)
{
	glm::mat4 Rotate;

	angle = angle / 180.0f * glm::pi<float>();

	glm::vec3 v = glm::normalize(u);

	float c = 1.0f - cos(angle), s = sin(angle);

	Rotate[0][0] = 1.0f + c * (v.x * v.x - 1.0f);
	Rotate[1][0] = c * v.x * v.y + v.z * s;
	Rotate[2][0] = c * v.x * v.z - v.y * s;
	Rotate[0][1] = c * v.x * v.y - v.z * s;
	Rotate[1][1] = 1.0f + c * (v.y * v.y - 1.0f);
	Rotate[2][1] = c * v.y * v.z + v.x * s;
	Rotate[0][2] = c * v.x * v.z + v.y * s;
	Rotate[1][2] = c * v.y * v.z - v.x * s;
	Rotate[2][2] = 1.0f + c * (v.z * v.z - 1.0f);

	return Rotate;
}
void Camera::MouseMove(int dx, int dy)
{
	float Sensitivity = 0.25f;

	pos -= ref;

	sf::Mouse::setPosition(sf::Vector2i(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2), *getWindow());
	getWindow()->setMouseCursorVisible(false);

	if (dx != 0)
	{
		float DeltaX = (float)dx * Sensitivity;

		x = (glm::vec3)(rotate(DeltaX, glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(x, 1.0f));
		y = (glm::vec3)(rotate(DeltaX, glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(y, 1.0f));
		z = (glm::vec3)(rotate(DeltaX, glm::vec3(0.0f,1.0f,0.0f)) * glm::vec4(z, 1.0f));
	}

	if (dy != 0)
	{
		float DeltaY = (float)dy * Sensitivity;

		y = (glm::vec3)(rotate(DeltaY, x) * glm::vec4(y, 1.0f));
		z = (glm::vec3)(rotate(DeltaY, x) * glm::vec4(z, 1.0f));

		if (y.y < 0.0f)
		{
			z = glm::vec3(0.0f, z.y > 0.0f ? 1.0f : -1.0f, 0.0f);
			y = glm::cross(z, x);
		}
	}

	pos = ref + z * glm::length(pos);

	up = y;
	right = x;
	forward = glm::cross(up, right);

	SetView();
}

void Camera::SetPerspective(float fovy, float aspect, float n, float f)
{
	projection = glm::perspective(fovy, aspect, n, f);
	projectionInverse = glm::inverse(projection);
	viewprojection = projection * view;
	vpMatrixInverse = viewInverse * projectionInverse;

	frustum.Set(vpMatrixInverse);
}

void Camera::SetOrtho(float width, float height)
{
	ortho = glm::ortho(0.0f, width, height, 0.0f, -1.0f, 1.0f);
	orthoInverse = glm::inverse(ortho);
}

void Camera::SetView()
{
	view = glm::mat4(x.x, y.x, z.x, 0.0f, x.y, y.y, z.y, 0.0f, x.z, y.z, z.z, 0.0f, -glm::dot(x, pos), -glm::dot(y, pos), -glm::dot(z, pos), 1.0f);
	viewInverse = glm::inverse(view);
	viewprojection = projection * view;
	vpMatrixInverse = viewInverse * projectionInverse;

	frustum.Set(vpMatrixInverse);
}

void Camera::CameraMovement(glm::vec3 &movement, glm::vec3 &camPos, float &height, float &offset)
{
	int newmousex;
	int newmousey;

	movement += glm::vec3(0.0f, height + offset - ref.y, 0.0f);

	Move(movement);

	newmousex = sf::Mouse::getPosition(*getWindow()).x - mousex;
	newmousey = sf::Mouse::getPosition(*getWindow()).y - mousey;

	MouseMove(newmousex, newmousey);

	mousex = sf::Mouse::getPosition(*getWindow()).x;
	mousey = sf::Mouse::getPosition(*getWindow()).y;
}

