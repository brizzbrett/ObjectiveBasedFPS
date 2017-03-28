#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "Model.hpp"
#include "Camera.hpp"

class Entity
{
protected: 

	Model* model; /**<entity's mesh */
	glm::mat4 modelMatrix;

	int active;

	glm::vec3 position; /**<Entity position */
	glm::vec3 scale; /**<Entity scale */
	glm::vec3 rotation; /**<Entity rotation */

public:

	/*
	* @brief Getter: the model
	* @return model
	*/
	Model* getModel() { return model; };

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
	Entity(Model* m, glm::vec3 pos=glm::vec3(0.0f, 0.0f, 0.0f));

	/*
	* @brief Entity destructor.
	*/
	~Entity();

	void Update();
	virtual void Render(Shader* s);
	
};

#endif
