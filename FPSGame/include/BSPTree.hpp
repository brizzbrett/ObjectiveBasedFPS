#pragma once

#include "BSPNode.hpp"

class BSPTree
{
private:
	BSPNode *Root;

private:
	BSPNode **VisibleGeometryNodes;
	int VisibleGeometryNodesCount;

public:
	BSPTree();
	~BSPTree();

private:
	void SetDefaults();

public:
	void Init(glm::vec3* Vertices, int *Indices, int IndicesCount, const glm::vec3 &Min, const glm::vec3 &Max, float MinAABBSize = 16.0f);
	void QuickSortVisibleGeometryNodes(int Left, int Right);
	void Render(bool VisualizeRenderingOrder);
	void RenderAABB(int Depth);
	void Destroy();
};