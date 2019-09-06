#include "Model.h"
#include <SFML/Graphics.hpp>

Model::Model(Mesh& mesh) {
	addData(mesh);
}

void Model::addData(Mesh& mesh)
{
	if (_VAO != 0) {
		deleteData();
	}

	glGenVertexArrays(1, &_VAO);
	glBindVertexArray(_VAO);

	_indicesCount = mesh.indices.size();

	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
}

void Model::deleteData()
{
	glDeleteVertexArrays(1, &_VAO);
	glDeleteBuffers(_buffers.size(), _buffers.data());

	_buffers.clear();

	_vboCount = 0;
	_VAO = 0;
}

void Model::addVBO(int dimensions, std::vector<GLfloat> data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(_vboCount, dimensions, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(_vboCount);
	_vboCount++;

	_buffers.push_back(vbo);
}

bool Model::bindVAO()
{
	if (_VAO = 0) {
		return false;
	}
	glBindVertexArray(_VAO);
	return true;
}

void Model::addEBO(const std::vector<GLuint> indices)
{
	GLuint ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW);
}