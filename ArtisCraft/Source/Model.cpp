#include "Model.h"
#include <SFML/Graphics.hpp>

Model::Model(Mesh& mesh) {
	addData(mesh);
}

void Model::addData(Mesh& mesh)
{
	if (m_VAO != 0) {
		deleteData();
	}

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	m_indicesCount = mesh.indices.size();

	addVBO(3, mesh.vertexPositions);
	addVBO(2, mesh.textureCoords);
	addEBO(mesh.indices);
}

void Model::deleteData()
{
	glDeleteVertexArrays(1, &m_VAO);
	glDeleteBuffers(m_buffers.size(), m_buffers.data());

	m_buffers.clear();

	m_vboCount = 0;
	m_VAO = 0;
}

void Model::addVBO(int dimensions, std::vector<GLfloat> data)
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(m_vboCount, dimensions, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(m_vboCount);
	m_vboCount++;

	m_buffers.push_back(vbo);
}

void Model::bindVAO()
{
	glBindVertexArray(m_VAO);
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