#include "MUtils.hpp"

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
			return 0;
		}
	}
	else
	{
		if (!img_data->loadFromFile(filepath))
		{
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