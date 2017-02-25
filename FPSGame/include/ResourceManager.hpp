#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <vector>
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "Terrain.hpp"

class ResourceManager
{

protected:

	std::vector<Shader*> *shaderArray; /**<Pointer to a vector array of Shader pointers */
	std::vector<VertexBuffer*> *vertexBufferArray; /**<Pointer to a vector array of VertexBuffer pointers */

	/*
	* @brief Resource Manager constructor. Internally created
	*/
	ResourceManager();

	/*
	* @brief Resource Manager destructor.
	*/
	~ResourceManager();

public:

	/*
	* @brief Getter: the pointer to the shader array
	* @return shaderArray
	*/
	std::vector<Shader*>* getShaderArray() { return shaderArray; };

	/*
	* @brief Getter: the pointer to the vertex buffer array
	* @return vertexBufferArray
	*/
	std::vector<VertexBuffer*>* getVertexBufferArray() { return vertexBufferArray; };

	/*
	* @brief Static function that returns the resource manager's memory location
	* @return Resource Manager's memory location
	*/
	static ResourceManager& getResourceManager();

	/*
	* @brief Destroys the Resource manager
	*/
	static void destroyResourceManager();

};

#endif