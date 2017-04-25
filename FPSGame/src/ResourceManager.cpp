#include "ResourceManager.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock deltaTime; /**<timer that tracks time since last iteration of game loop*/

ResourceManager::ResourceManager()
{

	shaderList = new std::vector<Shader*>();
	spriteList = new std::vector<SpriteRenderer*>();
	entityList = new std::vector<Entity*>();
	terrainList = new std::vector<Terrain>();

	Shader* terrain_S = new Shader("shaders/terrain_vs.glsl", "shaders/terrain_fs.glsl");
	Shader* model_S = new Shader("shaders/model_vs.glsl", "shaders/model_fs.glsl");
	Shader* sprite_S = new Shader("shaders/sprite_vs.glsl", "shaders/sprite_fs.glsl");
	//Shader* light_S = new Shader("shaders/light_vs.glsl", "shaders/light_fs.glsl");
	
	shaderList->push_back(terrain_S);
	shaderList->push_back(model_S);
	shaderList->push_back(sprite_S);

	SpriteRenderer* reticle = new SpriteRenderer(sprite_S, "Resources/UI/reticle.png");

	spriteList->push_back(reticle);

	Player* p = new Player(NULL);
	Entity* nanosuit = new Entity(new Model("Resources/models/player/nanosuit.obj"), glm::vec3(0.0f, 2.5f, 0.0f));
	Entity* lightsource = new Entity(new Model("Resources/models/lights/cube.obj"), glm::vec3(0.0f, 30.0f, 0.0f), LIGHT_SOURCE);


	entityList->push_back(p);
	entityList->push_back(nanosuit);
	
	Terrain terrain;

	if (terrain.InitTerrain("terrain.jpg") == -1) {
		slog("Cannot init terrain");
		exit(0);
	}

	terrainList->push_back(terrain);

	player = (Player*)entityList->at(0);

	float height = getTerrainList()->at(0).GetHeight(0.0f, 0.0f);
	float offset = 8.75f;

	player->camera.Look(glm::vec3(0.0f, height + offset, 0.0f), glm::vec3(0.0f, height + offset, -1.0f));
}

ResourceManager::~ResourceManager()
{
	for (std::vector<Shader*>::iterator it = shaderList->begin(); it != shaderList->end(); it++)
	{
		delete *it;
	}

	for (std::vector<SpriteRenderer*>::iterator it = spriteList->begin(); it != spriteList->end(); it++)
	{
		delete *it;
	}

	for (std::vector<Entity*>::iterator it = entityList->begin(); it != entityList->end(); it++)
	{
		delete *it;
	}

	delete shaderList;
	delete spriteList;
	delete entityList;
	delete terrainList;
}

ResourceManager& ResourceManager::getResourceManager()
{
	ResourceManager* rm = NULL;

	if (rm == NULL)
	{
		rm = new ResourceManager();
	}

	return *rm;
}

void ResourceManager::destroyResourceManager()
{
	ResourceManager* rm = &getResourceManager();
	delete rm;
}

void ResourceManager::UpdateAll()
{
	glm::vec3 movement = player->camera.KeyMove(deltaTime.getElapsedTime().asSeconds() * 0.5f);
	glm::vec3 camPos = player->camera.ref + movement;

	//slog("%f, %f, %f", player->camera.ref.x, player->camera.ref.y, player->camera.ref.z);
	camPos = terrainList->at(0).CheckCollision(player->camera, movement);

	player->setPosition(camPos);

	float height = terrainList->at(0).GetHeight(camPos.x, camPos.z);
	float offset = 8.75f;

	player->camera.CameraMovement(movement, camPos, height, offset);

	for (int i = 0; i < entityList->size(); i++)
	{
		entityList->at(i)->Update();
	}
	deltaTime.restart();
}
void ResourceManager::DrawAll() 
{
	
	Entity* tempLight = NULL;

	glUseProgram(shaderList->at(0)->getProgram());
	terrainList->at(0).Render(((Player*)entityList->at(0)), shaderList->at(0));

	for (int i = 0; i < entityList->size(); i++)
	{
		if (entityList->at(i)->type == LIGHT_SOURCE)
		{
			tempLight = entityList->at(i);
		}
		else
		{
			glUseProgram(shaderList->at(1)->getProgram());
			entityList->at(i)->Render(shaderList->at(1));
		}
	}

	/*if (tempLight)
	{
		glUseProgram(shaderList->at(3)->getProgram());
		tempLight->Render(shaderList->at(3));
	}*/

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//this should be disabled for UI and HUD stuffs, but enabled for 3D
	glDisable(GL_DEPTH_TEST);

	for (int i = 0; i < spriteList->size(); i++)
	{
		glUseProgram(shaderList->at(2)->getProgram());
		spriteList->at(i)->DrawSprite(player->camera, glm::vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT/2),glm::vec2(50,50));
	}

	glDisable(GL_BLEND);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

}
