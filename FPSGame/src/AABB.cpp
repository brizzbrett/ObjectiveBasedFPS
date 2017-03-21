#include "AABB.hpp"

AABB::AABB()
{
}

AABB::~AABB()
{
}

void AABB::Set(const glm::vec3 &min, const glm::vec3 &max)
{
	vertices[0] = glm::vec3(min.x, min.y, min.z);
	vertices[1] = glm::vec3(max.x, min.y, min.z);
	vertices[2] = glm::vec3(min.x, max.y, min.z);
	vertices[3] = glm::vec3(max.x, max.y, min.z);
	vertices[4] = glm::vec3(min.x, min.y, max.z);
	vertices[5] = glm::vec3(max.x, min.y, max.z);
	vertices[6] = glm::vec3(min.x, max.y, max.z);
	vertices[7] = glm::vec3(max.x, max.y, max.z);
}

bool AABB::PointInside(const glm::vec3 &Point)
{
	if (Point.x < vertices[0].x) return false;
	if (Point.y < vertices[0].y) return false;
	if (Point.z < vertices[0].z) return false;

	if (Point.x > vertices[7].x) return false;
	if (Point.y > vertices[7].y) return false;
	if (Point.z > vertices[7].z) return false;

	return true;
}

bool AABB::Visible(Frustum &frustum)
{
	return frustum.AABBVisible(vertices);
}

float AABB::Distance(Frustum &frustum)
{
	return frustum.AABBDistance(vertices);
}

void AABB::Render()
{
	glBegin(GL_LINES);

	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z); 
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z); 
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glEnd();
}
