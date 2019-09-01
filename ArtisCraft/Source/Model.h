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

	int getIndicesCount() { return _indicesCount; };

	void addVBO(int dimensions, std::vector<GLfloat> data);
	bool bindVAO();

private:
	void addEBO(const std::vector<GLuint> indices);

	GLuint _VAO;
	int _vboCount;
	int _indicesCount;
	std::vector<GLuint> _buffers;
};