#pragma once
#ifndef M_UTILS_H
#define M_UTILS_H

#include <string.h>
#include <sstream>
#include <iostream>
#include <glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>

typedef struct
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texels;
}Vertex;

typedef struct
{
	GLuint id;
	std::string type;
	aiString path;
}Texture;

GLuint LoadTexture(const char* filepath, bool model);


#endif