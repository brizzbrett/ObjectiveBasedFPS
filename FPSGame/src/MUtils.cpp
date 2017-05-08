#include "MUtils.hpp"
#include "SimpleLogger.hpp"

GLuint LoadTexture(const char* filepath, bool model)
{
	sf::Image *img_data = new sf::Image();
	sf::Vector2u size;
	if (model)
	{
		std::string text = "Resources/models/player/";

		text.append(filepath);


		if (!img_data->loadFromFile(text))
		{
			slog("Could not load");
			return 0;
		}
	}
	else
	{
		if (!img_data->loadFromFile(filepath))
		{
			slog("Could not load");
			return 0;
		}
	}
	size = img_data->getSize();
	GLuint textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data->getPixelsPtr());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	delete img_data;

	glBindTexture(GL_TEXTURE_2D, 0);

	return textureID;
}

GLuint LoadCubeMap(std::vector<const GLchar*> faces)
{
	GLuint textureID;
	sf::Image *img_data = new sf::Image();
	sf::Vector2u size;

	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++)
	{
		if (!img_data->loadFromFile(faces[i]))
		{
			slog("Could not load");
			return 0;
		}
		size = img_data->getSize();

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, img_data->getPixelsPtr());
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return textureID;
}