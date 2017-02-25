#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "BSPTree.hpp"
#include "TerrainTexturer.hpp"

class Terrain
{
private:

	int size, sizeP1;
	float sizeD2;

	glm::vec3 min, max;

	float *heights;

	int vertCount, indicesCount;

	GLuint vertbuffer, indexbuffer;

public:

	BSPTree BSPTree;

	Terrain();
	~Terrain();

	bool LoadTexture2D(char *FileName, float Scale = 256.0f, float Offset = -128.0f);
	void Render();
	void RenderAABB(int depth = -1);
	void Destroy();

	int GetSize() { return size; };
	glm::vec3 GetMin() { return min; };
	glm::vec3 GetMax() { return max; };
	void GetMinMax(glm::mat4 &ViewMatrix, glm::vec3 &min, glm::vec3 &max);
	int GetTrianglesCount(){ return indicesCount / 3; }

	int GetIndex(int X, int Z) { return sizeP1 * Z + X; };
	float GetHeight(int X, int Z) { return heights[GetIndex(X < 0 ? 0 : X > size ? size : X, Z < 0 ? 0 : Z > size ? size : Z)]; };

	float GetHeight(float X, float Z);	
	


private:
	float GetHeight(float *heights, int size, float X, float Z);
};

#endif