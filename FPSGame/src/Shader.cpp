#include <stdio.h>
#include <stdlib.h>
#include "shader.hpp"

#define MAX_STR_LEN 4096

GLuint g_shader_prog;

GLuint CreateShader(GLenum eShaderType, const char *strShaderFile)
{
	char shaderSource[4096];
	char inChar;
	FILE *shaderFile;
	int i = 0;
	GLuint shader;
	GLint status;
	GLint infoLogLength;
	GLchar strInfoLog[4096];
	char strShaderType[16];
	const char *ss;

	shaderFile = fopen(strShaderFile, "r");
	if (!shaderFile)
	{
		printf("failed to open shader file: %s\n", strShaderFile);
		return 0;
	}
	while (fscanf(shaderFile, "%c", &inChar) > 0)
	{
		shaderSource[i++] = inChar; //loading the file's chars into array
	}
	shaderSource[i - 1] = '\0';
	fclose(shaderFile);

	shader = glCreateShader(eShaderType);
	ss = shaderSource;
	glShaderSource(shader, 1, &ss, NULL);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		switch (eShaderType)
		{
		case GL_VERTEX_SHADER:
			sprintf(strShaderType, "vertex");
			break;
		case GL_GEOMETRY_SHADER:
			sprintf(strShaderType, "geometry");
			break;
		case GL_FRAGMENT_SHADER:
			sprintf(strShaderType, "fragment");
			break;
		}

		printf("Compile failure in %s shader:\n%s\n", strShaderType, strInfoLog);
		return 0;
	}

	return shader;
}

GLuint BuildShaderProgram(const char *vsPath, const char *fsPath)
{
	GLint infoLogLength;
	GLuint vertexShader;
	GLuint fragmentShader;
	GLuint program;
	GLint status;
	GLchar strInfoLog[4096];

	vertexShader = CreateShader(GL_VERTEX_SHADER, vsPath);
	fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fsPath);

	program = glCreateProgram();

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &status);

	if (status == GL_FALSE)
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);

		printf("Shader linker failure: %s\n", strInfoLog);
		return 0;
	}

	g_shader_prog = program;

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	return program;
}

/**
* @brief compiles a vertex and fragment shader and attaches it into a program
* @return id of compiled program
*/
GLuint ShadersInit()
{
	return BuildShaderProgram("shaders\\vs1.glsl", "shaders\\fs1.glsl");
}