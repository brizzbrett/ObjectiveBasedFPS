#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Model.hpp"
#include "Camera.hpp"
#include "BSPTree.hpp"

#define PLAYER 0
#define LIGHT_SOURCE 1
#define PLAYER_SPAWN 2
#define OTHER 3

class Entity
{
protected: 

	Entity* owner; /**<this entity's owner*/

	Model* model; /**<entity's mesh */
	glm::mat4 modelMatrix;
	
	bool active;

	

public:

	int type;
	
	glm::vec3 position; /**<Entity position */
	glm::vec3 scale; /**<Entity scale */
	glm::vec3 rotation; /**<Entity rotation */

	BSPTree tree; /**<The BSP Tree */

	/*
	* @brief Getter: the model
	* @return model
	*/
	Model* getModel() { return model; };

	void SetActive(bool set) { active = set; };

	bool IsActive() { return active; };

	/*
	* @brief Getter: the position
	* @return position
	*/
	glm::vec3 getPosition() { return position; };

	/*
	* @brief Setter: the position
	* @param pos position's new value
	*/
	void setPosition(glm::vec3 pos) { position = pos; };

	/*
	* @brief Getter: the scale
	* @return scale
	*/
	glm::vec3 getScale() { return scale; };

	/*
	* @brief Setter: the scale
	* @param sc scale's new value
	*/
	void setScale(glm::vec3 sc) { scale = sc; };

	/*
	* @brief Getter: the rotation
	* @return rotation
	*/
	glm::vec3 getRotation() { return rotation; };

	/*
	* @brief Setter: the rotation
	* @param rot rotation's new value in degrees
	*/
	void setRotation(glm::vec3 rot) { rotation = rot; };

	/*
	* @brief Entity constructor. Overloaded with 3 arguments.
	*/
	Entity(Model* m, glm::vec3 pos=glm::vec3(0.0f, 0.0f, 0.0f), int t=OTHER);

	/*
	* @brief Entity destructor.
	*/
	~Entity();

	void Update();
	virtual void Render(Shader* s);
	
};

#endif
