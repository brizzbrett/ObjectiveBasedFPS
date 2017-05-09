#pragma once
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include "Shader.hpp"
#include "VertexBuffer.hpp"
#include "Camera.hpp"
#include "Player.hpp"
#include "Terrain.hpp"
#include "SpriteRenderer.hpp"

class ResourceManager
{

protected:


	std::vector<Shader*> *shaderList; /**<Pointer to a vector array of Shader pointers */	
	std::vector<SpriteRenderer*> *spriteList; /**<Pointer to a vector array of Sprite pointers */
	std::vector<Entity*> *entityList; /**<Pointer to a vectory array of Entity pointers */
	std::vector<Terrain> *terrainList; /**<Pointer to a vector array of Terrains */

	bool aabbOn;

	GLuint skyboxVAO, skyboxVBO;
	GLuint cubemapTexture;

	glm::vec3 lightPos;
	/*
	* @brief Resource Manager constructor. Internally created
	*/
	ResourceManager();

	/*
	* @brief Resource Manager destructor.
	*/
	~ResourceManager();

public:
	Player* player;
	/*
	* @brief Getter: the pointer to the shader array
	* @return shaderList
	*/
	std::vector<Shader*>* getShaderList() { return shaderList; };

	/*
	* @brief Getter: the pointer to the sprite array
	* @return spriteList
	*/
	std::vector<SpriteRenderer*>* getSpriteList() { return spriteList; };

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

	void UpdateAll();
	void DrawAll();	

};

#endif