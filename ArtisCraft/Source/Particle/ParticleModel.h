#pragma once
#include <vector>
#include <GLM.h>

struct ParticleMesh {
	std::vector<GLfloat> vertexPositions;
	std::vector<GLuint> indices;
};

class ParticleModel {
public:
	ParticleModel() = default;

	ParticleModel(ParticleMesh& mesh);

	void addData(ParticleMesh& mesh);

	void deleteData();

	int getIndicesCount() { return _indicesCount; };

	void addVBO(int dimensions, std::vector<GLfloat> data);
	void bindVAO();

private:
	void addEBO(const std::vector<GLuint> indices);

	GLuint _VAO;
	int _vboCount;
	int _indicesCount;
	std::vector<GLuint> _buffers;
};