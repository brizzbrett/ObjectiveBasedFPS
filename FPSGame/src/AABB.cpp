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
