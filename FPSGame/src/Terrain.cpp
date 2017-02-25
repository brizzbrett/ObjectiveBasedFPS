#include "Terrain.hpp"

Terrain::Terrain()
{
	size = 0;
	sizeP1 = 0;
	sizeD2 = 0.0f;

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

bool Terrain::LoadTexture2D(char *FileName, float Scale, float Offset)
{
	Texture Texture;

	if (!Texture.LoadTexture2D(FileName))
	{
		return false;
	}

	if (Texture.GetWidth() != Texture.GetHeight())
	{
		Texture.Destroy();
		return false;
	}

	Destroy();

	size = Texture.GetWidth();
	sizeP1 = size + 1;
	sizeD2 = (float)size / 2.0f;

	vertCount = sizeP1 * sizeP1;

	float *TextureHeights = new float[size * size];

	glBindTexture(GL_TEXTURE_2D, Texture);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_GREEN, GL_FLOAT, TextureHeights);
	glBindTexture(GL_TEXTURE_2D, 0);

	Texture.Destroy();

	for (int i = 0; i < size * size; i++)
	{
		TextureHeights[i] = TextureHeights[i] * Scale + Offset;
	}

	heights = new float[vertCount];

	int i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			heights[i++] = GetHeight(TextureHeights, size, (float)x - 0.5f, (float)z - 0.5f);
		}
	}

	delete[] TextureHeights;

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

	min.x = min.z = -sizeD2;
	max.x = max.z = sizeD2;

	min.y = max.y = heights[0];

	for (int i = 1; i < vertCount; i++)
	{
		if (heights[i] < min.y) min.y = heights[i];
		if (heights[i] > max.y) max.y = heights[i];
	}

	Vertex *Vertices = new Vertex[vertCount];

	i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			Vertices[i].position = glm::vec3((float)x - sizeD2, heights[i], sizeD2 - (float)z);
			Vertices[i].normal = glm::normalize(glm::vec3(GetHeight(x - 1, z) - GetHeight(x + 1, z), 2.0f, GetHeight(x, z + 1) - GetHeight(x, z - 1)));

			i++;
		}
	}

	//vertbuffer = new VertexBuffer(Vertices, vertCount, GL_TRIANGLES, vertCount, 0, NULL);

	glGenBuffers(1, &vertbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertCount * sizeof(Vertex), Vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	indicesCount = size * size * 2 * 3;

	int *Indices = new int[indicesCount];

	i = 0;

	for (int z = 0; z < size; z++)
	{
		for (int x = 0; x < size; x++)
		{
			Indices[i++] = GetIndex(x, z);
			Indices[i++] = GetIndex(x + 1, z);
			Indices[i++] = GetIndex(x + 1, z + 1);

			Indices[i++] = GetIndex(x + 1, z + 1);
			Indices[i++] = GetIndex(x, z + 1);
			Indices[i++] = GetIndex(x, z);
		}
	}

	glGenBuffers(1, &indexbuffer);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesCount * sizeof(int), Indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	BSPTree.Init(Vertices, Indices, indicesCount, min, max);

	delete[] Vertices;
	delete[] Indices;

	return true;
}

void Terrain::Render()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertbuffer);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 0));

	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, sizeof(Vertex), (void*)(sizeof(glm::vec3) * 1));

	BSPTree.Render();

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terrain::RenderAABB(int depth)
{
	BSPTree.RenderAABB(depth);
}

void Terrain::Destroy()
{
	if (heights != NULL)
	{
		delete[] heights;
	}

	if (vertbuffer != 0)
	{
		glDeleteBuffers(1, &vertbuffer);
	}

	if (indexbuffer != 0)
	{
		glDeleteBuffers(1, &indexbuffer);
	}

	BSPTree.Destroy();

	size = 0;
	sizeP1 = 0;
	sizeD2 = 0.0f;

	min = max = glm::vec3(0.0f);

	heights = NULL;

	vertCount = 0;
	indicesCount = 0;

	vertbuffer = 0;
	indexbuffer = 0;
}

void Terrain::GetMinMax(glm::mat4 &ViewMatrix, glm::vec3 &min, glm::vec3 &max)
{
	int i = 0;

	for (int z = 0; z <= size; z++)
	{
		for (int x = 0; x <= size; x++)
		{
			glm::vec4 Position = ViewMatrix * glm::vec4((float)x - sizeD2, heights[i], sizeD2 - (float)z, 1.0f);

			if (i == 0)
			{
				min.x = max.x = Position.x;
				min.y = max.y = Position.y;
				min.z = max.z = Position.z;
			}
			else
			{
				if (Position.x < min.x) min.x = Position.x;
				if (Position.y < min.y) min.y = Position.y;
				if (Position.z < min.z) min.z = Position.z;

				if (Position.x > max.x) max.x = Position.x;
				if (Position.y > max.y) max.y = Position.y;
				if (Position.z > max.z) max.z = Position.z;
			}

			i++;
		}
	}
}

float Terrain::GetHeight(float X, float Z)
{
	Z = -Z;

	X += sizeD2;
	Z += sizeD2;

	float size = (float)this->size;

	if (X < 0.0f) X = 0.0f;
	if (X > size) X = size;
	if (Z < 0.0f) Z = 0.0f;
	if (Z > size) Z = size;

	int ix = (int)X, ixp1 = ix + 1;
	int iz = (int)Z, izp1 = iz + 1;

	float fx = X - (float)ix;
	float fz = Z - (float)iz;

	float a = GetHeight(ix, iz);
	float b = GetHeight(ixp1, iz);
	float c = GetHeight(ix, izp1);
	float d = GetHeight(ixp1, izp1);

	float ab = a + (b - a) * fx;
	float cd = c + (d - c) * fx;

	return ab + (cd - ab) * fz;
}

float Terrain::GetHeight(float *heights, int size, float X, float Z)
{
	float SizeM1F = (float)size - 1.0f;

	if (X < 0.0f) X = 0.0f;
	if (X > SizeM1F) X = SizeM1F;
	if (Z < 0.0f) Z = 0.0f;
	if (Z > SizeM1F) Z = SizeM1F;

	int ix = (int)X, ixp1 = ix + 1;
	int iz = (int)Z, izp1 = iz + 1;

	int SizeM1 = size - 1;

	if (ixp1 > SizeM1) ixp1 = SizeM1;
	if (izp1 > SizeM1) izp1 = SizeM1;

	float fx = X - (float)ix;
	float fz = Z - (float)iz;

	int izMSize = iz * size, izp1MSize = izp1 * size;

	float a = heights[izMSize + ix];
	float b = heights[izMSize + ixp1];
	float c = heights[izp1MSize + ix];
	float d = heights[izp1MSize + ixp1];

	float ab = a + (b - a) * fx;
	float cd = c + (d - c) * fx;

	return ab + (cd - ab) * fz;
}
