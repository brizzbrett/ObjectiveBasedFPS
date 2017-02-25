#pragma once
#ifndef TEXTURER_H
#define TEXTURER_H

#include <glew.h>
#include <glm/glm.hpp>
#include <FreeImage.h>

class Texture
{
private:
	GLuint texture;

	int width, height;

	FIBITMAP *GetBitmap(char *FileName, int &width, int &height, int &BPP);

public:

	Texture();
	~Texture();

	operator GLuint ();

	bool LoadTexture2D(char *FileName);
	void Destroy();

	int GetWidth() { return width; };
	int GetHeight() { return height; };
};

#endif