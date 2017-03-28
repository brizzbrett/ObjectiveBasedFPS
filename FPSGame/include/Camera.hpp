#ifndef CAMERA_H
#define CAMERA_H

#include "Game.hpp"

class Plane
{

protected:

	glm::vec3 normal;
	float normalDot;
	int order;

public:

	Plane();
	~Plane();

	void Set(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C);
	bool AABBBehind(const glm::vec3 *AABBVertices);
	float AABBDistance(const glm::vec3 *AABBVertices);
};

class Frustum
{

protected:

	glm::vec3 verts[8];

	Plane planes[6];

public:

	Frustum();
	~Frustum();

	void Set(const glm::mat4 &vpMatrixInverse);
	bool AABBVisible(const glm::vec3 *AABBVertices);
	float AABBDistance(const glm::vec3 *AABBVertices);
	void Render();
};

class Camera
{

protected:

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