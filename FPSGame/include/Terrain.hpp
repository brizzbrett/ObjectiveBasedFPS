#pragma once
#ifndef TERRAIN_H
#define TERRAIN_H

#include "BSPTree.hpp"
#include "HeightMap.hpp"
#include "Player.hpp"

class Terrain
{

protected:

	int size; /**<The width of the loaded texture */
	float halfSize; /**<half the value of size */

	glm::vec3 min, /**<half the size in the negative */
			max; /**<half the size in the positive */

	float *heights; /**<Array of floats with height data stored */

	GLuint vertbuffer, indexbuffer;

	int vertCount, /**<vert count */
		indicesCount; /**<index count */

	float GetHeight(float *heights, int size, float x, float z);

public:

	BSPTree tree; /**<The BSP Tree */

	/**
	* @brief Terrain Constructor - initalizes the protected values of the terrain
	*/
	Terrain();

	/**
	* @brief Terrain Destructor
	*/
	~Terrain();

	/**
	* @brief InitTerrain
	* @param file the grayscale image used to create the heightmap
	* @return an integer to determine if intialization was succesful or not
	*/
	int InitTerrain(char* file);

	/**
	* @brief LoadTexture2D
	* @param file the grayscale image used to create the heightmap
	* @param scale how extreme the heightmap is. (E.g. lower scale = smaller hills) Default: 256.0f
	* @param offset 
	* @return an integer to determine if intialization was succesful or not
	*/
	int LoadTexture2D(char *file, float scale = 256.0f, float offset = -128.0f);

	/**
	* @brief CheckVisibility
	* @param frustum a reference to the frustum for culling purposes
	* @return int to determine if visibility check was successful
	*/
	int CheckVisibility(Frustum &frustum);

	/**
	* @brief CheckCollision
	* @param cam a reference to the camera
	* @param movement determines movement based on the collision of the terrain
	* @return glm::vec3 of the new position
	*/
	glm::vec3 CheckCollision(Camera &cam, glm::vec3 movement);

	/**
	* @brief LoadTexture2D
	* @param frustum a reference to the frustum for culling purposes
	* @param s a shader
	*/
	void Render(Player* p, Shader* s);

	/**
	* @brief Destroy - resets all variables and clears up space
	*/
	void Destroy();

	/*
	* @brief Getter: the size
	* @return size
	*/
	int GetSize() { return size; };

	/*
	* @brief Getter: the minimum value
	* @return min
	*/
	glm::vec3 GetMin() { return min; };

	/*
	* @brief Getter: the maximum value
	* @return max
	*/
	glm::vec3 GetMax() { return max; };

	/*
	* @brief Getter: the index
	* @param x
	* @param z
	* @return the size plus 1 * the z plus the x
	*/
	int GetIndex(int x, int z) { return ((size+1) * z) + x; };

	/*
	* @brief Getter: the height of a specified index
	* @param x
	* @param z
	* @return height
	*/
	float GetHeight(int x, int z) { return heights[GetIndex(x < 0 ? 0 : x > size ? size : x, z < 0 ? 0 : z > size ? size : z)]; };

	/*
	* @brief Getter: the triangle count
	* @return indicesCount / 3
	*/
	int GetTrianglesCount(){ return indicesCount / 3; }


	/*
	* @brief Getter: gets the min and max based off the view
	*/
	void GetMinMax(glm::mat4 &view, glm::vec3 &min, glm::vec3 &max);

	/*
	* @brief Getter: the height
	* @return height
	*/
	float GetHeight(float x, float z);	
	
};

#endif