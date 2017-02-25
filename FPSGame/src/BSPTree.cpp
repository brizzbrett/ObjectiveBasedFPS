#include "BSPTree.hpp"

BSPTree::BSPTree()
{
	root = NULL;

	geometryNodes = NULL;
}

BSPTree::~BSPTree()
{
}

void BSPTree::Init(Vertex* vertices, int *indices, int indicesCount, const glm::vec3 &min, const glm::vec3 &max, float minAABBSize)
{
	Destroy();

	if (vertices != NULL && indices != NULL && indicesCount > 0)
	{
		root = new BSPNode();

		root->InitAABB(min, max, 0, minAABBSize);

		for (int i = 0; i < indicesCount; i += 3)
		{
			root->CheckTriangle(vertices, indices, i, i + 1, i + 2);
		}

		root->AllocateMemory();

		for (int i = 0; i < indicesCount; i += 3)
		{
			root->AddTriangle(vertices, indices, i, i + 1, i + 2);
		}

		root->ResetAABB(vertices);

		int nodesCount = root->InitIndexBufferObject();

		geometryNodes = new BSPNode*[nodesCount];
	}
}

void BSPTree::Render()
{
	if (geometryNodesCount > 0)
	{
		for (int i = 0; i < geometryNodesCount; i++)
		{
			geometryNodes[i]->Render();
		}
	}
}

void BSPTree::RenderAABB(int depth)
{
	if (root != NULL)
	{
		root->RenderAABB(depth);
	}
}

void BSPTree::Destroy()
{
	if (root != NULL)
	{
		root->Destroy();
		delete root;
	}

	if (geometryNodes != NULL)
	{
		delete[] geometryNodes;
	}

	root = NULL;

	geometryNodes = NULL;
}