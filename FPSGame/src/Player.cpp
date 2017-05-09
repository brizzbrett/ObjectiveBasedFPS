#include "Player.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 


Player::Player(Model* m, glm::vec3 pos) : Entity(m, pos)
{
	this->type = PLAYER;
	camera.SetPerspective(45.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.125f, 1024.0f);
	camera.SetOrtho((float)SCREEN_WIDTH,(float)SCREEN_HEIGHT);

	projectiles.reserve(1000);
}
void Player::Update()
{
	//slog("Updating Player...");
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		this->Fire();
		slog("Fire!");
	}

	for (int i = 0; i < projectiles.size(); i++)
	{
		float speed = 5.0;

		projectiles.at(i)->position += this->camera.forward*speed;
		projectiles.at(i)->Update();
	}
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

	if(model)
		model->Render(s);
	
	for (int i = 0; i < projectiles.size(); i++)
	{
		projectiles.at(i)->Render(s);
	}
}
void Player::Fire()
{
	Entity* ent = new Entity(new Model("Resources/models/lights/cube.obj"), this->camera.pos, 2);

	projectiles.push_back(ent);
}