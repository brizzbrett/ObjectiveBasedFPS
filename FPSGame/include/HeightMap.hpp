#pragma once
#ifndef HMAP_H
#define HMAP_H

#include <glew.h>
#include <glm/glm.hpp>
#include <FreeImage.h>

class HeightMap
{
private:
	GLuint texture;

	int width, height;

	FIBITMAP *GetBitmap(char *FileName, int &width, int &height, int &BPP);

public:

	HeightMap();
	~HeightMap();

	operator GLuint ();

	bool LoadTexture2D(char *FileName);
	void Destroy();

	int GetWidth() { return width; };
	int GetHeight() { return height; };
};

#endif