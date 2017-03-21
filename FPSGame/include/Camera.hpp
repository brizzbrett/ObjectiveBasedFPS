#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <math.h>
#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Game.hpp"

class Plane
{
private:
	glm::vec3 N;
	float ND;
	int O;

public:
	Plane();
	~Plane();

public:
	void Set(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C);
	bool AABBBehind(const glm::vec3 *AABBVertices);
	float AABBDistance(const glm::vec3 *AABBVertices);
};

class Frustum
{
private:
	glm::vec3 verts[8];

private:
	Plane planes[6];

public:
	Frustum();
	~Frustum();

public:
	void Set(const glm::mat4 &vpMatrixInverse);
	bool AABBVisible(const glm::vec3 *AABBVertices);
	float AABBDistance(const glm::vec3 *AABBVertices);
	void Render();
};

class Camera
{
private:

	int mousex;
	int mousey;

	void SetView();

public:

	Camera();
	~Camera();

	glm::vec3 x, y, z, pos, ref;

	glm::mat4 view, viewInverse, projection, projectionInverse, viewprojection, vpMatrixInverse;

	Frustum frustum;

	void Look(const glm::vec3 &pos, const glm::vec3 &ref, bool rotAroundRef = false);
	void Move(const glm::vec3 &movement);
	glm::vec3 KeyMove(float dt);
	void MouseMove(int dx, int dy);
	void SetPerspective(float fovy, float aspect, float n, float f);

	void CameraMovement(glm::vec3 &movement, glm::vec3 &camPos, float &height, float &offset);

};

#endif