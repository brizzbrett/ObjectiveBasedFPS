#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include "VertexBuffer.hpp"
#include "Camera.hpp"

class Entity
{
protected: 

	Camera* camera; /**<player's camera */
	VertexBuffer* vertexBuffer; /**<entity's vertex buffer data */

	glm::vec3 position; /**<Entity position */
	glm::vec3 scale; /**<Entity scale */
	glm::vec3 rotation; /**<Entity rotation */

public:

	/*
	* @brief Getter: the vertex buffer
	* @return vertexBuffer
	*/
	VertexBuffer* getVertexBuffer() { return vertexBuffer; };

	/*
	* @brief Setter: the vertex and color buffers
	* @param vbuff vertexBuffer's new value
	* @param cbuff colorBuffer's new value
	*/
	void setVertexBuffer(VertexBuffer* vbuff) { vertexBuffer = vbuff; };

	/*
	* @brief Getter: the camera
	* @return camera
	*/
	Camera* getCamera() { return camera; };

	/*
	* @brief Setter: the player camera
	* @param cam camera's new camera
	*/
	void setCamera(Camera* cam) { camera = cam; };

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
	Entity(VertexBuffer* vbuff, glm::vec3 pos);

	/*
	* @brief Entity destructor.
	*/
	~Entity();
};

#endif
