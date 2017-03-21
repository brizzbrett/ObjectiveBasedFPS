#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <iostream>
#include <vector>
#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "Camera.hpp"
#include "Entity.hpp"
#include "Terrain.hpp"

class ResourceManager
{

protected:

	std::vector<Shader*> *shaderList; /**<Pointer to a vector array of Shader pointers */
	std::vector<Entity*> *entityList; /**<Pointer to a vectory array of Entity pointers */
	std::vector<Terrain> *terrainList; /**<Pointer to a vector array of Terrains */

	/*
	* @brief Resource Manager constructor. Internally created
	*/
	ResourceManager();

	/*
	* @brief Resource Manager destructor.
	*/
	~ResourceManager();

public:
	Camera camera;
	/*
	* @brief Getter: the pointer to the shader array
	* @return shaderList
	*/
	std::vector<Shader*>* getShaderList() { return shaderList; };

	/*
	* @brief Getter: the pointer to the entity array
	* @return entityList
	*/
	std::vector<Entity*>* getEntityList() { return entityList; };

	/*
	* @brief Getter: the pointer to the terrain array
	* @return terrainList
	*/
	std::vector<Terrain>* getTerrainList() { return terrainList; };

	/*
	* @brief Static function that returns the resource manager's memory location
	* @return Resource Manager's memory location
	*/
	static ResourceManager& getResourceManager();

	/*
	* @brief Destroys the Resource manager
	*/
	static void destroyResourceManager();

	void Update(float dt);
	void Draw();
	

};

#endif