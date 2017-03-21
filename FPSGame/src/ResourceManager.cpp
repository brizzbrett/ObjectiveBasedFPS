#include "ResourceManager.hpp"

#define SCREEN_WIDTH 1280 /**<width of the window */ 
#define SCREEN_HEIGHT 720 /**<height of the window */ 

ResourceManager::ResourceManager()
{

	shaderList = new std::vector<Shader*>();

	Shader* shader = new Shader("shaders\\vs1.glsl", "shaders\\fs1.glsl", 0);

	shaderList->push_back(shader);

	entityList = new std::vector<Entity*>();

	terrainList = new std::vector<Terrain>();

	Terrain terrain;

	if (terrain.InitTerrain("terrain.jpg") == -1) {
		slog("Cannot init terrain");
		exit(0);
	}

	terrainList->push_back(terrain);
}

ResourceManager::~ResourceManager()
{
	for (std::vector<Shader*>::iterator it = shaderList->begin(); it != shaderList->end(); it++)
	{
		delete *it;
	}

	delete shaderList;

	for (std::vector<Entity*>::iterator it = entityList->begin(); it != entityList->end(); it++)
	{
		delete *it;
	}

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

void ResourceManager::Update(float dt)
{
	glm::mat4 model = glm::mat4(1.0f);

	getWindow()->clear(sf::Color::Transparent);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	GLuint PmatrixID = glGetUniformLocation(getShaderList()->at(0)->getProgram(), "Projection");
	glUniformMatrix4fv(PmatrixID, 1, GL_FALSE, &camera.projection[0][0]);

	GLuint VmatrixID = glGetUniformLocation(getShaderList()->at(0)->getProgram(), "View");
	glUniformMatrix4fv(VmatrixID, 1, GL_FALSE, &camera.view[0][0]);

	GLuint MmatrixID = glGetUniformLocation(getShaderList()->at(0)->getProgram(), "Model");
	glUniformMatrix4fv(MmatrixID, 1, GL_FALSE, &model[0][0]);

	glUseProgram(getShaderList()->at(0)->getProgram());

	glm::vec3 movement = camera.KeyMove(dt * 150.5f);

	glm::vec3 camPos = camera.ref + movement;

	slog("%f, %f, %f", camPos.x, camPos.y, camPos.z);
	camPos = getTerrainList()->at(0).CheckCollision(camera, movement);

	float height = getTerrainList()->at(0).GetHeight(camPos.x, camPos.z);
	float offset = 1.75f;

	camera.CameraMovement(movement, camPos, height, offset);

	getTerrainList()->at(0).Render(camera);
}