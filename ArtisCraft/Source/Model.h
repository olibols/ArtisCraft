#pragma once
#include <GLM.h>
#include <vector>

struct Mesh {
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> textureCoords;
	std::vector<GLuint> indices;
};

class Model {
public:
	Model() = default;

	Model(Mesh& mesh);

	void addData(Mesh& mesh);

	void deleteData();

	int getIndicesCount() { return m_indicesCount; };

	void addVBO(int dimensions, std::vector<GLfloat> data);
	void bindVAO();

private:
	void addEBO(const std::vector<GLuint> indices);

	GLuint m_VAO;
	int m_vboCount;
	int m_indicesCount;
	std::vector<GLuint> m_buffers;
};