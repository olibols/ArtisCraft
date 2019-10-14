#pragma once
#include "BasicTexture.h"

class TextureAtlas : public BasicTexture {
public:
	TextureAtlas(std::string textureFileName);

	std::vector<GLfloat> getTexture(const sf::Vector2i& coords);

private:
	int m_imageSize;
	int m_indvTexSize;

};