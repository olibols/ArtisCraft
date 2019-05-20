#include <GL/glew.h>
#include <vector>

class Model {
public:
	Model() = default;

	Model(std::vector<GLfloat> vertexPositions,
		std::vector<GLfloat> textureCoords,
		std::vector<GLuint> indices);
	~Model();

	void addData(std::vector<GLfloat> vertexPositions,
		std::vector<GLfloat> textureCoords,
		std::vector<GLuint> indices);

	void deleteData();

	void addVBO(int dimensions, std::vector<GLfloat> data);
	void bindVAO();

	int getIndicesCount();

private:
	void addEBO(std::vector<GLuint> indices);

	GLuint m_vao;
	int m_vboCount ;
	int m_indicesCount;
	std::vector<GLuint> m_buffers;
};