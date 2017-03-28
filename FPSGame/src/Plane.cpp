#include "Camera.hpp"

Plane::Plane()
{
}

Plane::~Plane()
{
}

void Plane::Set(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C)
{
	normal = glm::normalize(glm::cross(B - A, C - A));

	normalDot = glm::dot(normal, A);

	order = normal.z < 0.0f ? 
			(normal.y < 0.0f ? (normal.x < 0.0f ? 0 : 1) : 
			(normal.x < 0.0f ? 2 : 3)) : 
			(normal.y < 0.0f ? (normal.x < 0.0f ? 4 : 5) : 
			(normal.x < 0.0f ? 6 : 7));
}

bool Plane::AABBBehind(const glm::vec3 *AABBVertices)
{
	return glm::dot(normal, AABBVertices[order]) < normalDot;
}

float Plane::AABBDistance(const glm::vec3 *AABBVertices)
{
	return glm::dot(normal, AABBVertices[order]);
}