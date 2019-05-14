#include "BaseTexture.h"
#include <SFML/Graphics.hpp>


BaseTexture::BaseTexture(std::string filename){
	loadFromFile(filename); // Just calles loadFromFile
}


BaseTexture::~BaseTexture()	{
	glDeleteTextures(1, &m_id); // Deletes the texture from memory
}

void BaseTexture::loadFromFile(std::string filename){
	
	sf::Image i;
	i.loadFromFile("Resources/Textures/Blocks/" + filename + ".png");

	glGenTextures(1, &m_id); // Generate a texutre and put the ID into m_id
	glBindTexture(GL_TEXTURE_2D, m_id); // Bind the texture to make it current
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i.getSize().x, i.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, i.getPixelsPtr()); // Give the texture object in openGL the actual texture

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This cluster just set various different parameters in the texture, like aliasing and texture clamping.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

}

void BaseTexture::bindTexture(){
	glBindTexture(GL_TEXTURE_2D, m_id); // Rebinds the texture for reuse after being unbound.
}
