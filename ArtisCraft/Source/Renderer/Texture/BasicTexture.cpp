#include "BasicTexture.h"
#include "stb_image.h"
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <SFML/Graphics.hpp>

BasicTexture::BasicTexture(std::string filename) {
	loadFromFile(filename); // Just calles loadFromFile
}


BasicTexture::~BasicTexture() {
	glDeleteTextures(1, &_ID); // Deletes the texture from memory
}

void BasicTexture::loadFromFile(std::string filename) {

	int width, height, nrChannels;
	unsigned char *data = stbi_load(std::string("../Resources/Textures/Blocks/" + filename + ".png").c_str(), &width, &height, &nrChannels, 0);
	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &_ID);

	glBindTexture(GL_TEXTURE_2D, _ID);


	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else {
		printf("Failed to generate texture :(");
	}
	
}

void BasicTexture::bindTexture() {
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _ID); // Rebinds the texture for reuse after being unbound.
}