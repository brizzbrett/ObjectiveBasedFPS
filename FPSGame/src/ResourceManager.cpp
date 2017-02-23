#include "ResourceManager.hpp"

static const GLfloat g_vertex_buffer_data[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
};

// One color for each vertex. They were generated randomly.
static const GLfloat g_color_buffer_data[] = {
	-4.583f,  0.771f,  0.014f,
	0.609f,  0.115f,  0.436f,
	0.327f,  0.483f,  0.844f,
	0.822f,  -4.569f,  0.201f,
	0.435f,  0.602f,  0.223f,
	0.310f,  0.747f,  0.185f,
	-4.597f,  0.770f,  0.761f,
	-4.559f,  0.436f,  0.730f,
	0.359f,  -4.583f,  0.152f,
	0.483f,  -4.596f,  0.789f,
	-4.559f,  0.861f,  0.639f,
	0.195f,  -4.548f,  0.859f,
	0.014f,  0.184f,  -4.576f,
	0.771f,  0.328f,  0.970f,
	0.406f,  0.615f,  0.116f,
	0.676f,  0.977f,  0.133f,
	0.971f,  -4.572f,  0.833f,
	0.140f,  0.616f,  0.489f,
	0.997f,  -4.513f,  0.064f,
	0.945f,  0.719f,  -4.592f,
	-4.543f,  0.021f,  0.978f,
	0.279f,  0.317f,  -4.505f,
	0.167f,  0.620f,  0.077f,
	0.347f,  0.857f,  0.137f,
	0.055f,  0.953f,  0.042f,
	0.714f,  -4.505f,  0.345f,
	0.783f,  0.290f,  0.734f,
	0.722f,  0.645f,  0.174f,
	0.302f,  0.455f,  0.848f,
	0.225f,  -4.587f,  0.040f,
	-4.517f,  0.713f,  0.338f,
	0.053f,  0.959f,  0.120f,
	0.393f,  0.621f,  0.362f,
	0.673f,  0.211f,  0.457f,
	0.820f,  0.883f,  0.371f,
	0.982f,  0.099f,  0.879f
};

ResourceManager::ResourceManager()
{
	shaderArray = new std::vector<Shader*>();

	Shader* shader = new Shader("shaders\\vs1.glsl", "shaders\\fs1.glsl");

	shaderArray->push_back(shader);

	vertexBufferArray = new std::vector<VertexBuffer*>();

	VertexBuffer* vertbuffer = new VertexBuffer(g_vertex_buffer_data, sizeof(g_vertex_buffer_data), GL_TRIANGLES, 12 * 3, sizeof(GLfloat) * 3);
	VertexBuffer* colorbuffer = new VertexBuffer(g_color_buffer_data, sizeof(g_color_buffer_data), GL_TRIANGLES, 12 * 3, 0);

	vertexBufferArray->push_back(vertbuffer);
	vertexBufferArray->push_back(colorbuffer);
}

ResourceManager::~ResourceManager()
{
	delete shaderArray;
	delete vertexBufferArray;
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