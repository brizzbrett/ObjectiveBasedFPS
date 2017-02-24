#pragma once
#ifndef BSPNODE_H
#define BSPNODE_H

#include "AABB.hpp"

class BSPNode
{
private:

	glm::vec3 Min, Max;

	int Depth;

	AABB aabb;

	bool Visible;
	float Distance;

	int *Indices;

	int IndicesCount;

	GLuint IndexBufferObject;

	BSPNode *Children[2];

	void SetDefaults();

public:

	void InitAABB(const glm::vec3 &Min, const glm::vec3 &Max, int Depth, float MinAABBSize);
	bool CheckTriangle(glm::vec3* Vertices, int *Indices, int A, int B, int C);
	void AllocateMemory();
	bool AddTriangle(glm::vec3* Vertices, int *Indices, int A, int B, int C);
	void ResetAABB(glm::vec3* Vertices);
	int InitIndexBufferObject();
	float GetDistance();
	void Render();
	void RenderAABB(int Depth);
	void Destroy();

	BSPNode();
	~BSPNode();

};

#endif