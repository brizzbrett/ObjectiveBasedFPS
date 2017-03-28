#include "ResourceManager.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

static sf::Clock deltaTime; /**<timer that tracks time since last iteration of game loop*/

ResourceManager::ResourceManager()
{

	shaderList = new std::vector<Shader*>();
	entityList = new std::vector<Entity*>();
	terrainList = new std::vector<Terrain>();

	Shader* shader = new Shader("shaders\\vs1.glsl", "shaders\\fs1.glsl");

	shaderList->push_back(shader);

	Player* p = new Player(NULL);
	Entity* nanosuit = new Entity(new Model("Resources/models/player/nanosuit.obj"), glm::vec3(0.0f, 0.0f, 0.0f));
	Entity* girl = new Entity(new Model("Resources/models/player/bgirl.obj"), glm::vec3(0.0f, 0.0f, 0.0f));

	entityList->push_back(p);
	entityList->push_back(nanosuit);
	
	Terrain terrain;

	if (terrain.InitTerrain("terrain.jpg") == -1) {
		slog("Cannot init terrain");
		exit(0);
	}

	terrainList->push_back(terrain);

	player = (Player*)entityList->at(0);
}

ResourceManager::~ResourceManager()
{
	for (std::vector<Shader*>::iterator it = shaderList->begin(); it != shaderList->end(); it++)
	{
		delete *it;
	}

	for (std::vector<Entity*>::iterator it = entityList->begin(); it != entityList->end(); it++)
	{
		delete *it;
	}

	delete shaderList;
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
	float offset = 1.75f;

	player->camera.CameraMovement(movement, camPos, height, offset);

	for (int i = 0; i < entityList->size(); i++)
	{
		entityList->at(i)->Update();
	}
	deltaTime.restart();
}
void ResourceManager::DrawAll() 
{
	terrainList->at(0).Render(((Player*)entityList->at(0))->camera);

	for (int i = 0; i < entityList->size(); i++)
	{
		entityList->at(i)->Render(shaderList->at(0));
	}
	
}
