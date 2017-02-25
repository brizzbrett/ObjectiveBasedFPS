#pragma once
#ifndef BSPNODE_H
#define BSPNODE_H

#include "VertexBuffer.hpp"
#include "AABB.hpp"

class BSPNode
{
private:

	glm::vec3 min, max; /**<aabb */

	int depth; /**<aabb */

	AABB aabb; /**<aabb */
	
	bool visible; /**<aabb */

	int *indices; /**<pointer to each index */

	int indicesCount; /**<number of indices */

	VertexBuffer* indexbuffer; /**<vertex buffer for each node */
	GLuint IndexBufferObject;

	BSPNode *left; /**<the left child node */
	BSPNode *right; /**<the right child node */

public:

	BSPNode();
	~BSPNode();

	void InitAABB(const glm::vec3 &min, const glm::vec3 &max, int depth, float minAABBSize);
	bool CheckTriangle(Vertex* vertices, int *indices, int A, int B, int C);
	void AllocateMemory();
	bool AddTriangle(Vertex* vertices, int *indices, int A, int B, int C);
	void ResetAABB(Vertex* vertices);
	int InitIndexBufferObject();
	void Render();
	void RenderAABB(int depth);
	void Destroy();



};

#endif