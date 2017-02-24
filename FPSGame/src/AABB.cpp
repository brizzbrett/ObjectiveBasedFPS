#include "AABB.hpp"

AABB::AABB()
{
}

AABB::~AABB()
{
}

void AABB::Set(const glm::vec3 &Min, const glm::vec3 &Max)
{
	Vertices[0] = glm::vec3(Min.x, Min.y, Min.z);
	Vertices[1] = glm::vec3(Max.x, Min.y, Min.z);
	Vertices[2] = glm::vec3(Min.x, Max.y, Min.z);
	Vertices[3] = glm::vec3(Max.x, Max.y, Min.z);
	Vertices[4] = glm::vec3(Min.x, Min.y, Max.z);
	Vertices[5] = glm::vec3(Max.x, Min.y, Max.z);
	Vertices[6] = glm::vec3(Min.x, Max.y, Max.z);
	Vertices[7] = glm::vec3(Max.x, Max.y, Max.z);
}

bool AABB::PointInside(const glm::vec3 &Point)
{
	if (Point.x < Vertices[0].x) return false;
	if (Point.y < Vertices[0].y) return false;
	if (Point.z < Vertices[0].z) return false;

	if (Point.x > Vertices[7].x) return false;
	if (Point.y > Vertices[7].y) return false;
	if (Point.z > Vertices[7].z) return false;

	return true;
}

void AABB::Render()
{
	glBegin(GL_LINES);

	glVertex3fv(&Vertices[0][0]); glVertex3fv(&Vertices[1][0]);
	glVertex3fv(&Vertices[2][0]); glVertex3fv(&Vertices[3][0]);
	glVertex3fv(&Vertices[4][0]); glVertex3fv(&Vertices[5][0]);
	glVertex3fv(&Vertices[6][0]); glVertex3fv(&Vertices[7][0]);

	glVertex3fv(&Vertices[0][0]); glVertex3fv(&Vertices[2][0]);
	glVertex3fv(&Vertices[1][0]); glVertex3fv(&Vertices[3][0]);
	glVertex3fv(&Vertices[4][0]); glVertex3fv(&Vertices[6][0]);
	glVertex3fv(&Vertices[5][0]); glVertex3fv(&Vertices[7][0]);

	glVertex3fv(&Vertices[0][0]); glVertex3fv(&Vertices[4][0]);
	glVertex3fv(&Vertices[1][0]); glVertex3fv(&Vertices[5][0]);
	glVertex3fv(&Vertices[2][0]); glVertex3fv(&Vertices[6][0]);
	glVertex3fv(&Vertices[3][0]); glVertex3fv(&Vertices[7][0]);

	glEnd();
}
