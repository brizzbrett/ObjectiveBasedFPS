#include "SpriteRenderer.hpp"


SpriteRenderer::SpriteRenderer(Shader* s, std::string filepath) :
shader(s)
{
	// Configure VAO/VBO
	GLuint vertexbuffer;
	GLfloat vertices[] = {
		// Pos      // Tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	texture.id = LoadTexture(&filepath[0], false);
	texture.path = filepath;
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteVertexArrays(1, &this->vao);
}

void SpriteRenderer::DrawSprite(Camera &cam, glm::vec2 position, glm::vec2 size, GLfloat rotate, glm::vec3 color)
{
	glUseProgram(shader->getProgram());
	glm::mat4 model;
	glm::vec2 center_position = glm::vec2(position.x - (size.x / 2), position.y - (size.y / 2));

	model = glm::translate(model, glm::vec3(center_position, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

	model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f)); // Move origin of rotation to center of quad
	model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f)); // Then rotate
	model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f)); // Move origin back

	model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "model"), 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(shader->getProgram(), "projection"), 1, GL_FALSE, &cam.ortho[0][0]);

	// Render textured quad
	glUniform3f(glGetUniformLocation(shader->getProgram(), "spriteColor"), color.x, color.y, color.z);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture.id);

	glBindVertexArray(this->vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}