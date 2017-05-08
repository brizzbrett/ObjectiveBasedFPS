#pragma once
#ifndef AABB_H
#define AABB_H

#include "MUtils.hpp"
#include "Camera.hpp"

class AABB
{
private:

	glm::vec3 vertices[8]; /**<array of vertices */

public:	
	
	AABB();
	~AABB();

	void Set(const glm::vec3 &min, const glm::vec3 &max);
	bool PointInside(const glm::vec3 &Point);

	bool Visible(Frustum &frustum);
	float Distance(Frustum &frustum);

	void Render();

};


#endif