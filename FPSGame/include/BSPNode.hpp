#pragma once
#ifndef BSPNODE_H
#define BSPNODE_H

#include "Mesh.hpp"
#include "AABB.hpp"

class BSPNode
{
private:

	glm::vec3 min, max; /**<aabb */

	int depth; /**<aabb */

	AABB aabb; /**<aabb */
	
	bool visible; /**<aabb */
	float distance;

	int *indices; /**<pointer to each index */

	int indicesCount; /**<number of indices */

	BSPNode *left; /**<the left child node */
	BSPNode *right; /**<the right child node */

public:

	BSPNode();
	~BSPNode();
	GLuint indexbuffer;
	void Split(const glm::vec3 &min, const glm::vec3 &max, int depth, float minAABBSize);
	bool CheckTriangle(Vertex* vertices, GLuint* indices, int A, int B, int C);
	void AllocateMemory();
	bool AddTriangle(Vertex* vertices, GLuint* indices, int A, int B, int C);
	void ResetAABB(Vertex* vertices);
	int InitIndexBufferObject();
	int CheckVisibility(Frustum &frustum, BSPNode **geometryNodes, int &geometryNodesCount);
	void Render();
	void Destroy();


	float BSPNode::GetDistance() { return distance; };

};

#endif