#include "Camera.hpp"

Frustum::Frustum()
{
}

Frustum::~Frustum()
{
}

void Frustum::Set(const glm::mat4 &vpMatrixInverse)
{
	glm::vec4 A = vpMatrixInverse * glm::vec4(-1.0f, -1.0f, 1.0f, 1.0f);
	glm::vec4 B = vpMatrixInverse * glm::vec4(1.0f, -1.0f, 1.0f, 1.0f);
	glm::vec4 C = vpMatrixInverse * glm::vec4(-1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 D = vpMatrixInverse * glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 E = vpMatrixInverse * glm::vec4(-1.0f, -1.0f, -1.0f, 1.0f);
	glm::vec4 F = vpMatrixInverse * glm::vec4(1.0f, -1.0f, -1.0f, 1.0f);
	glm::vec4 G = vpMatrixInverse * glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f);
	glm::vec4 H = vpMatrixInverse * glm::vec4(1.0f, 1.0f, -1.0f, 1.0f);

	verts[0] = glm::vec3(A.x / A.w, A.y / A.w, A.z / A.w);
	verts[1] = glm::vec3(B.x / B.w, B.y / B.w, B.z / B.w);
	verts[2] = glm::vec3(C.x / C.w, C.y / C.w, C.z / C.w);
	verts[3] = glm::vec3(D.x / D.w, D.y / D.w, D.z / D.w);
	verts[4] = glm::vec3(E.x / E.w, E.y / E.w, E.z / E.w);
	verts[5] = glm::vec3(F.x / F.w, F.y / F.w, F.z / F.w);
	verts[6] = glm::vec3(G.x / G.w, G.y / G.w, G.z / G.w);
	verts[7] = glm::vec3(H.x / H.w, H.y / H.w, H.z / H.w);

	planes[0].Set(verts[4], verts[0], verts[2]);
	planes[1].Set(verts[1], verts[5], verts[7]);
	planes[2].Set(verts[4], verts[5], verts[1]);
	planes[3].Set(verts[2], verts[3], verts[7]);
	planes[4].Set(verts[0], verts[1], verts[3]);
	planes[5].Set(verts[5], verts[4], verts[6]);
}

bool Frustum::AABBVisible(const glm::vec3 *AABBVertices)
{
	for (int i = 0; i < 6; i++)
	{
		if (planes[i].AABBBehind(AABBVertices))
		{
			return false;
		}
	}

	return true;
}

float Frustum::AABBDistance(const glm::vec3 *AABBVertices)
{
	return planes[5].AABBDistance(AABBVertices);
}

void Frustum::Render()
{
	/*glBegin(GL_LINES);

	glVertex3fv((GLfloat*)&verts[0]); glVertex3fv((GLfloat*)&verts[1]);
	glVertex3fv((GLfloat*)&verts[2]); glVertex3fv((GLfloat*)&verts[3]);
	glVertex3fv((GLfloat*)&verts[4]); glVertex3fv((GLfloat*)&verts[5]);
	glVertex3fv((GLfloat*)&verts[6]); glVertex3fv((GLfloat*)&verts[7]);

	glVertex3fv((GLfloat*)&verts[0]); glVertex3fv((GLfloat*)&verts[2]);
	glVertex3fv((GLfloat*)&verts[1]); glVertex3fv((GLfloat*)&verts[3]);
	glVertex3fv((GLfloat*)&verts[4]); glVertex3fv((GLfloat*)&verts[6]);
	glVertex3fv((GLfloat*)&verts[5]); glVertex3fv((GLfloat*)&verts[7]);

	glVertex3fv((GLfloat*)&verts[0]); glVertex3fv((GLfloat*)&verts[4]);
	glVertex3fv((GLfloat*)&verts[1]); glVertex3fv((GLfloat*)&verts[5]);
	glVertex3fv((GLfloat*)&verts[2]); glVertex3fv((GLfloat*)&verts[6]);
	glVertex3fv((GLfloat*)&verts[3]); glVertex3fv((GLfloat*)&verts[7]);

	glEnd();*/
}