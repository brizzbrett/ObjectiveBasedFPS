#include "BSPTree.hpp"

BSPTree::BSPTree()
{
	root = NULL;

	geometryNodes = NULL;
}

BSPTree::~BSPTree()
{
}

void BSPTree::Init(Vertex* vertices, GLuint* indices, int indicesCount, const glm::vec3 &min, const glm::vec3 &max, float minAABBSize)
{
	Destroy();

	if (indicesCount > 0)
	{
		root = new BSPNode();

		root->Split(min, max, 0, minAABBSize);

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

void BSPTree::QuickSortVisibleGeometryNodes(int Left, int Right)
{
	float Pivot = geometryNodes[(Left + Right) / 2]->GetDistance();
	int i = Left, j = Right;

	while (i <= j)
	{
		while (geometryNodes[i]->GetDistance() < Pivot) i++;
		while (geometryNodes[j]->GetDistance() > Pivot) j--;

		if (i <= j)
		{
			if (i != j)
			{
				BSPNode *Temp = geometryNodes[i];
				geometryNodes[i] = geometryNodes[j];
				geometryNodes[j] = Temp;
			}

			i++;
			j--;
		}
	}

	if (Left < j)
	{
		QuickSortVisibleGeometryNodes(Left, j);
	}

	if (i < Right)
	{
		QuickSortVisibleGeometryNodes(i, Right);
	}
}

int BSPTree::CheckVisibility(Frustum &frustum)
{
	int TrianglesRendered = 0;

	geometryNodesCount = 0;

	if (root != NULL)
	{
		TrianglesRendered = root->CheckVisibility(frustum, geometryNodes, geometryNodesCount);

		if (geometryNodesCount > 1)
		{
			QuickSortVisibleGeometryNodes(0, geometryNodesCount - 1);
		}

	}

	return TrianglesRendered;
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