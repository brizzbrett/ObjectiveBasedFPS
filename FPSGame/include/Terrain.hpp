#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "BSPTree.hpp"
#include "TerrainTexturer.hpp"

class Terrain
{
private:

	int size;
	float halfSize;

	glm::vec3 min, max;

	float *heights;

	int vertCount, indicesCount;

	GLuint vertbuffer, indexbuffer;

public:

	BSPTree tree;

	Terrain();
	~Terrain();

	int InitTerrain(char* file);
	int LoadTexture2D(char *FileName, float Scale = 256.0f, float Offset = -128.0f);
	int CheckVisibility(Frustum &frustum, bool SortVisibleGeometryNodes);
	glm::vec3 CheckCollision(Camera cam, glm::vec3 movement);

	void Render(Camera cam);
	void Destroy();

	int GetSize() { return size; };
	glm::vec3 GetMin() { return min; };
	glm::vec3 GetMax() { return max; };
	void GetMinMax(glm::mat4 &view, glm::vec3 &min, glm::vec3 &max);
	int GetTrianglesCount(){ return indicesCount / 3; }

	int GetIndex(int x, int z) { return ((size+1) * z) + x; };
	float GetHeight(int x, int z) { return heights[GetIndex(x < 0 ? 0 : x > size ? size : x, z < 0 ? 0 : z > size ? size : z)]; };

	float GetHeight(float x, float z);	
	


private:
	float GetHeight(float *heights, int size, float x, float z);
};

#endif