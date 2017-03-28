#include "HeightMap.hpp"
#include "SimpleLogger.hpp"

int gl_max_texture_size = 1024, gl_max_texture_max_anisotropy_ext = 1024;

HeightMap::HeightMap()
{
	texture = 0;

	width = 0;
	height = 0;
}

HeightMap::~HeightMap()
{
}

HeightMap::operator GLuint ()
{
	return texture;
}

FIBITMAP *HeightMap::GetBitmap(char *FileName, int &width, int &height, int &BPP)
{
	FREE_IMAGE_FORMAT fif = FreeImage_GetFileType(FileName);

	if (fif == FIF_UNKNOWN)
	{
		fif = FreeImage_GetFIFFromFilename(FileName);
	}

	if (fif == FIF_UNKNOWN)
	{
		slog("File format not known...");
		return NULL;
	}

	FIBITMAP *dib = NULL;

	if (FreeImage_FIFSupportsReading(fif))
	{
		dib = FreeImage_Load(fif, FileName);
		slog("Free image supports this file format...");
	}

	if (dib != NULL)
	{
		slog("dib made it here...");
		int OriginalWidth = FreeImage_GetWidth(dib);
		int OriginalHeight = FreeImage_GetHeight(dib);

		width = OriginalWidth;
		height = OriginalHeight;

		if (width == 0 || height == 0)
		{
			FreeImage_Unload(dib);
			slog("Could not unload dib");
			return NULL;
		}

		BPP = FreeImage_GetBPP(dib);

		if (width > gl_max_texture_size) width = gl_max_texture_size;
		if (height > gl_max_texture_size) height = gl_max_texture_size;

		if (!GLEW_ARB_texture_non_power_of_two)
		{
			width = 1 << (int)floor((log((float)width) / log(2.0f)) + 0.5f);
			height = 1 << (int)floor((log((float)height) / log(2.0f)) + 0.5f);
		}

		if (width != OriginalWidth || height != OriginalHeight)
		{
			FIBITMAP *rdib = FreeImage_Rescale(dib, width, height, FILTER_BICUBIC);
			FreeImage_Unload(dib);
			dib = rdib;
		}
	}

	return dib;
}

bool HeightMap::LoadTexture2D(char *FileName)
{

	int width, height, BPP;

	FIBITMAP *dib = GetBitmap(FileName, width, height, BPP);

	if (dib == NULL)
	{
		slog("dib is null...");
		return false;
	}

	GLenum Format = 0;

	if (BPP == 32) Format = GL_BGRA;
	if (BPP == 24) Format = GL_BGR;

	if (Format == 0)
	{
		FreeImage_Unload(dib);
		return false;
	}

	Destroy();

	glGenTextures(1, &texture);

	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (GLEW_EXT_texture_filter_anisotropic)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, gl_max_texture_max_anisotropy_ext);
	}
	glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, Format, GL_UNSIGNED_BYTE, FreeImage_GetBits(dib));

	glBindTexture(GL_TEXTURE_2D, 0);

	FreeImage_Unload(dib);

	return true;
}

void HeightMap::Destroy()
{
	if (texture != 0)
	{
		glDeleteTextures(1, &texture);
	}

	texture = 0;

	width = 0;
	height = 0;
}