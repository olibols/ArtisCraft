#include "Model.h"

Model::Model() {

}

Model::~Model() {
	destroy();
}

void Model::draw() {

}

void Model::draw(glm::mat4 projectionMatrix, glm::mat4 viewMatrix) {

}

void Model::update() {

}

void Model::setProgram(GLuint programID) {
	this->programID = programID;
}

GLuint Model::getVao() {
	return vaoID;
}

std::vector<GLuint> Model::getVBOs()
{
	return VBOs;
}

void Model::destroy() {
	glDeleteVertexArrays(1, &vaoID);
	glDeleteBuffers(VBOs.size(), &VBOs.front[0]);
	VBOs.clear();

	for (auto t : textures) {
		t.second.~BasicTexture();
	}
	textures.clear();
}

void Model::setTexture(std::string textureName, BasicTexture texture) {
	textures[textureName] = texture;
}

BasicTexture Model::getTexture(std::string textureName) {
	return textures.at(textureName);
}