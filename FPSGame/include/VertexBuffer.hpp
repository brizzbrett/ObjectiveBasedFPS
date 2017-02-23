#pragma once
#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <iostream>
#include <glew.h>
#include <glm/glm.hpp>
#include "Shader.hpp"

class VertexBuffer
{
protected:

	GLuint vertexBufferID; /**< */
	Shader* shader; /**< */
	GLenum mode; /**< */
	GLsizei count; /**< */
	GLsizei stride; /**< */

public:

	/*
	* @brief VertexBuffer constructor. Overloaded to take a GLvoid* and the GLsizeiptr
	* @param data the data being passed into the vertex buffer.
	* @param size the size of the data to allocate
	*/
	VertexBuffer(const GLvoid* data, GLsizeiptr size, GLenum m, GLsizei c, GLsizei s, Shader* sr);

	/*
	* @brief Camera destructor.
	*/
	~VertexBuffer();

	/*
	* @brief Getter: the vertex buffer
	* @return vertexBuffer
	*/
	GLuint getVertexBuffer(){ return vertexBufferID; };

	/*
	* @brief Getter: the shader
	* @return shader
	*/
	Shader* getShader() { return shader; };

	void configureVertexAttributes();
	void renderVertexBuffer();
};

typedef VertexBuffer ColorBuffer; /**<VertexBuffer and ColorBuffer are interchangeable*/

#endif