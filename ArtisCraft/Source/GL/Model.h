#pragma once

#include <vector>
#include <gl/glew.h>

// The small struct for holding vertex positions etc.
struct Mesh {
	std::vector<GLfloat> vertexPositions;
	std::vector<GLfloat> vertexColors;
	std::vector<GLuint> indices;
};


// The class that holds the OpenGL stuff and can be rendered.
class Model {
public:
	Model() = default;

	Model(const Mesh mesh);
	void addData(const Mesh mesh);

	int getIndiceCount();

	void addVBO(int dimensions, std::vector<GLfloat> data);
	void bindVAO();

private:
	void addEBO(std::vector<GLuint> indices);

	GLuint m_VAO;

	int m_VBOcount;
	int m_indiceCount;
	std::vector<GLuint> m_buffers;
};