#include "Player.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

Player::Player(Model* m, glm::vec3 pos) : Entity(m, pos)
{
	camera.SetPerspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.125f, 1024.0f);
}
void Player::Render(Shader* s)
{
	glm::mat4 modelMatrix = glm::mat4(1.0f);

	GLuint PmatrixID = glGetUniformLocation(s->getProgram(), "Projection");
	glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, &camera.projection[0][0]);

	GLuint VmatrixID = glGetUniformLocation(s->getProgram(), "View");
	glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, &camera.view[0][0]);

	GLuint MmatrixID = glGetUniformLocation(s->getProgram(), "Model");
	glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, &modelMatrix[0][0]);

	glUseProgram(s->getProgram());

	if(model)
		model->Render(s);
}