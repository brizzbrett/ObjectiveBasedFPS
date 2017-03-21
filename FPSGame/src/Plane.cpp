#include "Camera.hpp"

Plane::Plane()
{
}

Plane::~Plane()
{
}

void Plane::Set(const glm::vec3 &A, const glm::vec3 &B, const glm::vec3 &C)
{
	N = glm::normalize(glm::cross(B - A, C - A));
	ND = glm::dot(N, A);
	O = N.z < 0.0f ? (N.y < 0.0f ? (N.x < 0.0f ? 0 : 1) : (N.x < 0.0f ? 2 : 3)) : (N.y < 0.0f ? (N.x < 0.0f ? 4 : 5) : (N.x < 0.0f ? 6 : 7));
}

bool Plane::AABBBehind(const glm::vec3 *AABBVertices)
{
	return glm::dot(N, AABBVertices[O]) < ND;
}

float Plane::AABBDistance(const glm::vec3 *AABBVertices)
{
	return glm::dot(N, AABBVertices[O]);
}