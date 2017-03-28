#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.hpp"

class Player : public Entity
{

protected:

public:
	Camera camera;

	Player(Model* m, glm::vec3 pos=glm::vec3(0.0f,0.0f,0.0f));
	~Player();

	void Update();
	void Render(Shader* s);

};

#endif