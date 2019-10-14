#include "TextureAtlas.h"

TextureAtlas::TextureAtlas(std::string textureFileName)
{
	sf::Image i;

	if (!i.loadFromFile("../Resources/Textures/" + textureFileName + ".png")) {
		throw std::runtime_error("Unable to open image: " + textureFileName);
	}
	loadFromImage(i);

	m_imageSize = 256;
	m_indvTexSize = 16;
}

std::vector<GLfloat> TextureAtlas::getTexture(const sf::Vector2i & coords)
{
	const float PER_ROW = (float)m_imageSize / (float)m_indvTexSize;
	const float TEX_SIZE = 1.0f / PER_ROW;
	const float PIXEL_SIZE = 1.0f / (float)m_imageSize;

	GLfloat xMin = (coords.x * TEX_SIZE);
	GLfloat yMin = (coords.y * TEX_SIZE);

	GLfloat xMax = (xMin + TEX_SIZE);
	GLfloat yMax = (yMin + TEX_SIZE);

	return
	{
		xMax, yMax,
		xMin, yMax,
		xMin, yMin,
		xMax, yMin
	};
}