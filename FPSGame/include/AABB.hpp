#pragma once
#ifndef AABB_H
#define AABB_H

#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>

class AABB
{
private:
	glm::vec3 Vertices[8];

public:
	void Set(const glm::vec3 &Min, const glm::vec3 &Max);
	bool PointInside(const glm::vec3 &Point);
	/*bool Visible(CFrustum &Frustum);
	float Distance(CFrustum &Frustum);*/
	void Render();

	AABB();
	~AABB();
};


#endif