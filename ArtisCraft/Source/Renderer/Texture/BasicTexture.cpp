#include "BasicTexture.h"
#include <SFML/Graphics.hpp>

BasicTexture::BasicTexture(std::string filename) {
	loadFromFile(filename); // Just calles loadFromFile
}


BasicTexture::~BasicTexture() {
	glDeleteTextures(1, &textureID); // Deletes the texture from memory
}

void BasicTexture::loadFromFile(std::string filename) {

	sf::Image i;
	i.loadFromFile("../Resources/Textures/Blocks/" + filename + ".png");

	glGenTextures(1, &textureID); // Generate a texutre and put the ID into m_id
	glBindTexture(GL_TEXTURE_2D, textureID); // Bind the texture to make it current

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr()); // Give the texture object in openGL the actual texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This cluster just set various different parameters in the texture, like aliasing and texture clamping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

void BasicTexture::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, textureID); // Rebinds the texture for reuse after being unbound.
}