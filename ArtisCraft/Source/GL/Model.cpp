#include "Model.h"

Model::Model(Mesh mesh)
{
	addData(mesh);
}

void Model::addData(Mesh mesh)
{

	if (m_VAO != 0) {
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(m_buffers.size(), m_buffers.data());
		m_buffers.clear();
		m_VBOcount = 0;
		m_VAO = 0;
	}

	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	m_indiceCount = mesh.indices.size();

	addVBO(3, mesh.vertexPositions);
	addEBO(mesh.indices);
}

int Model::getIndiceCount()
{
	return 0;
}

void Model::addVBO(int dimensions, std::vector<GLfloat> data)
{
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(m_VBOcount, dimensions, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);

	glEnableVertexAttribArray(m_VBOcount);
	m_VBOcount++;

	m_buffers.push_back(VBO);
}

void Model::bindVAO()
{
	glBindVertexArray(m_VAO);
}

void Model::addEBO(std::vector<GLuint> indices)
{
	GLuint EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		indices.size() * sizeof(GLuint),
		indices.data(),
		GL_STATIC_DRAW);
}
