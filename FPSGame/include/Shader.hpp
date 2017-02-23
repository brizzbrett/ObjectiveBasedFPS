#pragma once
#ifndef _SHADER_H_
#define _SHADER_H_
#include <glew.h>

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
	Shader(const char *vsPath, const char *fsPath, GLuint vertA);

	/*
	* @brief Shader Destructor: deletes the program
	*/
	~Shader();

};

#endif 