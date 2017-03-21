#include "Terrain.hpp"

Terrain::Terrain()
{
	size = 0;
	halfSize = 0.0f;

	min = max = glm::vec3(0.0f);

	heights = NULL;

	vertCount = 0;
	indicesCount = 0;

	vertbuffer = 0;
	indexbuffer = 0;
}

Terrain::~Terrain()
{
}

int Terrain::InitTerrain(char* file)
{
	
	if (LoadTexture2D("terrain.jpg", 32.0f, -16.0f) == -1)
	{
		return -1;
	}

	Vertex *verts = new Vertex[vertCount];

	int i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			verts[i].position = glm::vec3((float)x - halfSize, heights[i], halfSize - (float)z);
			verts[i].normal = glm::normalize(glm::vec3(GetHeight(x - 1, z) - GetHeight(x + 1, z), 2.0f, GetHeight(x, z + 1) - GetHeight(x, z - 1)));

			i++;
		}
	}

	slog("verts: %i", vertCount);

	glGenBuffers(1, &vertbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), verts, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	indicesCount = size * size * 2 * 3;

	int *indices = new int[indicesCount];

	slog("Indices: %i", indicesCount);

	i = 0;

	for (int z = 0; z < size; z++)
	{
		for (int x = 0; x < size; x++)
		{
			indices[i++] = GetIndex(x, z);
			indices[i++] = GetIndex(x + 1, z);
			indices[i++] = GetIndex(x + 1, z + 1);

			indices[i++] = GetIndex(x + 1, z + 1);
			indices[i++] = GetIndex(x, z + 1);
			indices[i++] = GetIndex(x, z);
		}
	}

	glGenBuffers(1, &indexbuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(int), indices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	tree.Init(verts, indices, indicesCount, min, max);

	delete[] verts;
	delete[] indices;

	return 0;
}
int Terrain::LoadTexture2D(char *FileName, float Scale, float Offset)
{
	Texture texture;

	if (!texture.LoadTexture2D(FileName))
	{
		return -1;
	}

	if (texture.GetWidth() != texture.GetHeight())
	{
		texture.Destroy();
		return -1;
	}

	Destroy();

	size = texture.GetWidth();
	halfSize = (float)size / 2.0f;

	vertCount = (size+1) * (size+1);

	float *textureHeights = new float[size * size];

	glBindTexture(GL_TEXTURE_2D, texture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_GREEN, GL_FLOAT, textureHeights);
	glBindTexture(GL_TEXTURE_2D, 0);

	texture.Destroy();

	for (int i = 0; i < size * size; i++)
	{
		textureHeights[i] = textureHeights[i] * Scale + Offset;
	}

	heights = new float[vertCount];

	int i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			heights[i++] = GetHeight(textureHeights, size, (float)x - 0.5f, (float)z - 0.5f);
		}
	}

	delete[] textureHeights;

	float *SmoothedHeights = new float[vertCount];

	i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			SmoothedHeights[i] = 0.0f;

			SmoothedHeights[i] += GetHeight(x - 1, z + 1) + GetHeight(x, z + 1) * 2 + GetHeight(x + 1, z + 1);
			SmoothedHeights[i] += GetHeight(x - 1, z) * 2 + GetHeight(x, z) * 3 + GetHeight(x + 1, z) * 2;
			SmoothedHeights[i] += GetHeight(x - 1, z - 1) + GetHeight(x, z - 1) * 2 + GetHeight(x + 1, z - 1);

			SmoothedHeights[i] /= 15.0f;

			i++;
		}
	}

	delete[] heights;

	heights = SmoothedHeights;

	min.x = min.z = -halfSize;
	max.x = max.z = halfSize;

	min.y = max.y = heights[0];

	for (int i = 1; i < vertCount; i++)
	{
		if (heights[i] < min.y) min.y = heights[i];
		if (heights[i] > max.y) max.y = heights[i];
	}

	return 0;
}

int Terrain::CheckVisibility(Frustum &frustum, bool SortVisibleGeometryNodes)
{
	return tree.CheckVisibility(frustum, SortVisibleGeometryNodes);
}

glm::vec3 Terrain::CheckCollision(Camera cam, glm::vec3 movement)
{
	glm::vec3 camPos = cam.ref + movement;
	glm::vec3 min = GetMin();
	glm::vec3 max = GetMax();

	if (camPos.x < min.x) movement += glm::vec3(min.x - camPos.x, 0.0f, 0.0f);
	if (camPos.x > max.x) movement += glm::vec3(max.x - camPos.x, 0.0f, 0.0f);
	if (camPos.z < min.z) movement += glm::vec3(0.0f, 0.0f, min.z - camPos.z);
	if (camPos.z > max.z) movement += glm::vec3(0.0f, 0.0f, max.z - camPos.z);

	return camPos;
}

void Terrain::Render(Camera cam)
{
	CheckVisibility(cam.frustum, true);

	glColor3f(1.0f, 1.0f, 1.0f);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	tree.Render();

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::Destroy()
{
	if (heights != NULL)
	{
		delete[] heights;
	}

	tree.Destroy();

	size = 0;
	halfSize = 0.0f;

	min = max = glm::vec3(0.0f);

	heights = NULL;

	vertCount = 0;
	indicesCount = 0;

	vertbuffer = 0;
	indexbuffer = 0;
}

void Terrain::GetMinMax(glm::mat4 &view, glm::vec3 &min, glm::vec3 &max)
{
	int i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			glm::vec4 pos = view * glm::vec4((float)x - halfSize, heights[i], halfSize - (float)z, 1.0f);

			if (i == 0)
			{
				min.x = max.x = pos.x;
				min.y = max.y = pos.y;
				min.z = max.z = pos.z;
			}
			else
			{
				if (pos.x < min.x) min.x = pos.x;
				if (pos.y < min.y) min.y = pos.y;
				if (pos.z < min.z) min.z = pos.z;

				if (pos.x > max.x) max.x = pos.x;
				if (pos.y > max.y) max.y = pos.y;
				if (pos.z > max.z) max.z = pos.z;
			}

			i++;
		}
	}
}

float Terrain::GetHeight(float x, float z)
{
	z = -z;

	x += halfSize;
	z += halfSize;

	float size = (float)this->size;

	if (x < 0.0f) x = 0.0f;
	if (x > size) x = size;
	if (z < 0.0f) z = 0.0f;
	if (z > size) z = size;

	int ix = (int)x, ixp1 = ix + 1;
	int iz = (int)z, izp1 = iz + 1;

	float fx = x - (float)ix;
	float fz = z - (float)iz;

	float a = GetHeight(ix, iz);
	float b = GetHeight(ixp1, iz);
	float c = GetHeight(ix, izp1);
	float d = GetHeight(ixp1, izp1);

	float ab = a + (b - a) * fx;
	float cd = c + (d - c) * fx;

	return ab + (cd - ab) * fz;
}

float Terrain::GetHeight(float *heights, int size, float x, float z)
{
	float SizeM1F = (float)size - 1.0f;

	if (x < 0.0f) x = 0.0f;
	if (x > SizeM1F) x = SizeM1F;
	if (z < 0.0f) z = 0.0f;
	if (z > SizeM1F) z = SizeM1F;

	int ix = (int)x, ixp1 = ix + 1;
	int iz = (int)z, izp1 = iz + 1;

	int SizeM1 = size - 1;

	if (ixp1 > SizeM1) ixp1 = SizeM1;
	if (izp1 > SizeM1) izp1 = SizeM1;

	float fx = x - (float)ix;
	float fz = z - (float)iz;

	int izMSize = iz * size, izp1MSize = izp1 * size;

	float a = heights[izMSize + ix];
	float b = heights[izMSize + ixp1];
	float c = heights[izp1MSize + ix];
	float d = heights[izp1MSize + ixp1];

	float ab = a + (b - a) * fx;
	float cd = c + (d - c) * fx;

	return ab + (cd - ab) * fz;
}
