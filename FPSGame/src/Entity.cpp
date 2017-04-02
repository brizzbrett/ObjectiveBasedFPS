#include "Entity.hpp"

Entity::Entity(Model* m, glm::vec3 pos) :
model(m), position(pos)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
}
Entity::~Entity()
{

}
void Entity::Update()
{
	modelMatrix = glm::translate(glm::mat4(1.0f), this->position);
}
void Entity::Render(Shader* s)
{
	GLuint MmatrixID = glGetUniformLocation(s->getProgram(), "Model");
	glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

	if(model)
		model->Render(s);
}