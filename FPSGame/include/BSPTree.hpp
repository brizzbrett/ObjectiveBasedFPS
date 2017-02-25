#pragma once
#ifndef BSPTREE_H
#define BSPTREE_H

#include "BSPNode.hpp"

class BSPTree
{
private:
	BSPNode *root; /**<the root node of the tree */

	BSPNode **geometryNodes; /**<array of nodes that hold geometry */
	int geometryNodesCount; /**<number of nodes that hold geometry */

public:	
	
	BSPTree();
	~BSPTree();

	void Init(Vertex* vertices, int *indices, int indicesCount, const glm::vec3 &min, const glm::vec3 &max, float minAABBSize = 16.0f);
	void Render();
	void RenderAABB(int depth);	
	void Destroy();
	

};

#endif