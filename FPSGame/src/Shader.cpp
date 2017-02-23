#include <stdio.h>
#include <stdlib.h>
#include "shader.hpp"

GLuint Shader::CreateShader(GLenum shaderType, const char *shaderFileStr)
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

	shaderFile = fopen(shaderFileStr, "r");
	if (!shaderFile)
	{
		printf("failed to open shader file: %s\n", shaderFileStr);
		return 0;
	}
	while (fscanf(shaderFile, "%c", &inChar) > 0)
	{
		shaderSource[i++] = inChar; //loading the file's chars into array
	}
	shaderSource[i - 1] = '\0';
	fclose(shaderFile);

	shader = glCreateShader(shaderType);
	ss = shaderSource;
	glShaderSource(shader, 1, &ss, NULL);

	glCompileShader(shader);

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		switch (shaderType)
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

Shader::Shader(const char *vsPath, const char *fsPath)
{
	GLint infoLogLength;
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
		exit(1);
	}

	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	glUseProgram(program);

}
Shader::~Shader()
{
	glDeleteProgram(program);
}