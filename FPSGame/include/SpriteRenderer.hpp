#pragma once
#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "MUtils.hpp"
#include "Shader.hpp"
#include "Camera.hpp"


class SpriteRenderer
{
public:

	SpriteRenderer(Shader* s, std::string filepath);
	~SpriteRenderer();
	
	void DrawSprite(Camera &cam, glm::vec2 position, glm::vec2 size = glm::vec2(10, 10), GLfloat rotate = 0.0f, glm::vec3 color = glm::vec3(1.0f));

private:

	Shader* shader;
	Texture texture;
	GLuint vao;

};

#endif