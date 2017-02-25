#pragma once
#ifndef AABB_H
#define AABB_H

#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include "Vertex.hpp"

class AABB
{
private:
	glm::vec3 vertices[8]; /**<array of vertices */

public:	
	
	AABB();
	~AABB();

	void Set(const glm::vec3 &min, const glm::vec3 &max);
	bool PointInside(const glm::vec3 &Point);
	void Render();

};


#endif