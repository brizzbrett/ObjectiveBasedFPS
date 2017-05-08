#include "BSPNode.hpp"

BSPNode::BSPNode()
{
	min = max = glm::vec3(0.0f);

	depth = 0;

	indices = NULL;

	indicesCount = 0;

	indexbuffer = 0;

	left = NULL;
	right = NULL;
}

BSPNode::~BSPNode()
{
}

void BSPNode::Split(const glm::vec3 &min, const glm::vec3 &max, int depth, float minAABBSize)
{
	this->min = min;
	this->max = max;

	this->depth = depth;

	glm::vec3 mid = (min + max) / 2.0f;
	glm::vec3 size = max - min;

	aabb.Set(min, max);

	if (size.x > minAABBSize || size.z > minAABBSize)
	{
		left = new BSPNode();
		right = new BSPNode();

		if (size.x >= size.z)
		{
			left->Split(glm::vec3(min.x, min.y, min.z), glm::vec3(mid.x, max.y, max.z), depth + 1, minAABBSize);
			right->Split(glm::vec3(mid.x, min.y, min.z), glm::vec3(max.x, max.y, max.z), depth + 1, minAABBSize);
		}
		else
		{
			left->Split(glm::vec3(min.x, min.y, min.z), glm::vec3(max.x, max.y, mid.z), depth + 1, minAABBSize);
			right->Split(glm::vec3(min.x, min.y, mid.z), glm::vec3(max.x, max.y, max.z), depth + 1, minAABBSize);
		}
	}
}

bool BSPNode::CheckTriangle(Vertex* vertices, GLuint* indices, int A, int B, int C)
{
	if (aabb.PointInside(vertices[indices[A]].position))
	{
		if (aabb.PointInside(vertices[indices[B]].position))
		{
			if (aabb.PointInside(vertices[indices[C]].position))
			{
				bool childHasVerts = false;

				if (left != NULL)
				{
					childHasVerts |= left->CheckTriangle(vertices, indices, A, B, C);
				}

				if (right != NULL && !childHasVerts)
				{
					childHasVerts |= right->CheckTriangle(vertices, indices, A, B, C);
				}

				if (!childHasVerts)
				{
					indicesCount += 3;
				}

				return true;
			}
		}
	}

	return false;
}

void BSPNode::AllocateMemory()
{
	if (indicesCount > 0)
	{
		indices = new int[indicesCount];
		indicesCount = 0;
	}

	if (left != NULL)
	{
		left->AllocateMemory();
	}

	if (right != NULL)
	{
		right->AllocateMemory();
	}
}

bool BSPNode::AddTriangle(Vertex* vertices, GLuint* indices, int A, int B, int C)
{
	if (aabb.PointInside(vertices[indices[A]].position))
	{
		if (aabb.PointInside(vertices[indices[B]].position))
		{
			if (aabb.PointInside(vertices[indices[C]].position))
			{
				bool childHasVerts = false;

				if (left != NULL)
				{
					childHasVerts |= left->AddTriangle(vertices, indices, A, B, C);
				}

				if (right != NULL && !childHasVerts)
				{
					childHasVerts |= right->AddTriangle(vertices, indices, A, B, C);
				}

				if (!childHasVerts)
				{
					this->indices[indicesCount++] = indices[A];
					this->indices[indicesCount++] = indices[B];
					this->indices[indicesCount++] = indices[C];
				}

				return true;
			}
		}
	}

	return false;
}

void BSPNode::ResetAABB(Vertex* vertices)
{
	float minY = min.y, maxY = max.y;

	min.y = maxY;
	max.y = minY;

	if (indicesCount > 0)
	{
		for (int i = 0; i < indicesCount; i++)
		{
			if (vertices[indices[i]].position.y < min.y) min.y = vertices[indices[i]].position.y;
			if (vertices[indices[i]].position.y > max.y) max.y = vertices[indices[i]].position.y;
		}
	}

	if (left != NULL)
	{
		left->ResetAABB(vertices);

		if (left->min.y < min.y) min.y = left->min.y;
		if (left->max.y > max.y) max.y = left->max.y;
	}

	if (right != NULL)
	{
		right->ResetAABB(vertices);

		if (right->min.y < min.y) min.y = right->min.y;
		if (right->max.y > max.y) max.y = right->max.y;
	}

	aabb.Set(min, max);
}

int BSPNode::InitIndexBufferObject()
{
	int nodesCount = 0;

	if (indicesCount > 0)
	{

		glGenBuffers(1, &indexbuffer);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(GLuint), indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		delete[] indices;
		indices = NULL;

		nodesCount++;
	}

	if (left != NULL)
	{
		nodesCount += left->InitIndexBufferObject();
	}

	if (right != NULL)
	{
		nodesCount += right->InitIndexBufferObject();
	}

	return nodesCount;
}

int BSPNode::CheckVisibility(Frustum &frustum, BSPNode **geometryNodes, int &geometryNodesCount)
{
	int TrianglesRendered = 0;

	visible = aabb.Visible(frustum);

	if (true)
	{
		if (indicesCount > 0)
		{
			distance = aabb.Distance(frustum);

			geometryNodes[geometryNodesCount++] = this;

			TrianglesRendered += indicesCount / 3;
		}

		if (left != NULL)
		{
			TrianglesRendered += left->CheckVisibility(frustum, geometryNodes, geometryNodesCount);
		}

		if (right != NULL)
		{
			TrianglesRendered += right->CheckVisibility(frustum, geometryNodes, geometryNodesCount);
		}
	}

	return TrianglesRendered;
}

void BSPNode::Render(Shader* s)
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void BSPNode::RenderAABB(int Depth)
{
	if (visible)
	{
		if (Depth == -1 || Depth == this->depth)
		{
			aabb.Render();
		}

		if (left != NULL)
		{
			left->RenderAABB(Depth);
		}

		if (right != NULL)
		{
			right->RenderAABB(Depth);
		}
	}
}

void BSPNode::Destroy()
{
	if (indices != NULL)
	{
		delete[] indices;
	}	
	
	if (indexbuffer != 0)
	{
		glDeleteBuffers(1, &indexbuffer);
	}

	if (left != NULL)
	{
		left->Destroy();
		delete left;
	}

	if (right != NULL)
	{
		right->Destroy();
		delete right;
	}

	min = max = glm::vec3(0.0f);

	depth = 0;

	indices = NULL;

	indicesCount = 0;

	indexbuffer = 0;

	left = NULL;
	right = NULL;
}