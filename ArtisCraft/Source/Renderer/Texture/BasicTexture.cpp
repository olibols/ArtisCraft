#include "BasicTexture.h"
#include <iostream>
#include <SFML/Graphics.hpp>



BasicTexture::BasicTexture(std::string filename) {
	loadFromFile(filename); // Just calles loadFromFile
}


BasicTexture::~BasicTexture() {
	glDeleteTextures(1, &_ID); // Deletes the texture from memory
}

void BasicTexture::loadFromImage(sf::Image image){
	glGenTextures(1, &_ID);
	glBindTexture(GL_TEXTURE_2D, _ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getSize().x, image.getSize().y,
		0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());
	glGenerateMipmap(GL_TEXTURE_2D);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void BasicTexture::loadFromFile(std::string file)
{
	sf::Image i;
	if (!i.loadFromFile("../Resources/Textures/Blocks/" + file + ".png"))
	{
		
	}

	loadFromImage(i);
}

void BasicTexture::bindTexture() {
	
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ID); // Rebinds the texture for reuse after being unbound.
}