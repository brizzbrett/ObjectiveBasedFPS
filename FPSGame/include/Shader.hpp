#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_

#include <glew.h>
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/type_ptr.hpp>

#include "SimpleLogger.hpp"

class Shader
{

protected:

	GLuint program; /**<the shader program */
	GLuint vertexShader; /**<the vertex shader data */
	GLuint fragmentShader; /**<the fragment shader data */
	GLuint vertexAttrib; /**<the vertex attribute */

	/*
	* @brief Creates a shader from a file
	* @param shaderType the type of shader (E.g. VERTEX, FRAGMENT, GEOMETRY)
	* @param shaderFileStr a string of the file path for the shader
	* @return the shader data
	*/
	GLuint CreateShader(GLenum shaderType, const char *shaderFileStr);

public:

	/*
	* @brief Getter: get's the shader program
	* @return the shader program
	*/
	GLuint getProgram() { return program; };

	/*
	* @brief Getter: get's the vertex attribute
	* @return the vertex attribute
	*/
	GLuint getVertexAttrib() { return vertexAttrib; };

	/*
	* @brief Shader Constructor: has two overloads for vertex shader file path and fragment shader filepath
	* @param vsPath a string of the vertex shader file path
	* @param fsPath a string of the fragment shader file path
	*/
	Shader(const char *vsPath, const char *fsPath);

	/*
	* @brief Shader Destructor: deletes the program
	*/
	~Shader();

};

#endif 