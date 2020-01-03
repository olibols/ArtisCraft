#include "BlockRenderer.h"

BlockRenderer::BlockRenderer()
{
	Mesh mesh;
	mesh.vertexPositions =
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1
	};

	mesh.indices = {
		0, 1, 2,
		2, 3, 0,

		4, 5, 6,
		6, 7, 4,

		8, 9, 10,
		10, 11, 8,

		12, 13, 14,
		14, 15, 12,

		16, 17, 18,
		18, 19, 16,

		20, 21, 22,
		22, 23, 20
	};

	m_cubeModel.addData(mesh);
}

void BlockRenderer::addBlock(glm::vec3 position)
{
	m_positions.push_back(position);
}

void BlockRenderer::render(Camera & cam)
{
	m_shader.useProgram();
	m_cubeModel.bindVAO();
	m_shader.loadProjViewMatrix(cam.getProjViewMatrix());

	for (auto pos : m_positions) {
		m_shader.loadModelMatrix(makeModelMatrix({ pos.x, pos.y, pos.z }, { 0.0, 0.0, 0.0 }));
		glDrawElements(GL_TRIANGLES, m_cubeModel.getIndiceCount(), GL_UNSIGNED_INT, 0);
		printf("Pong! \n");
	}

	m_positions.clear();
}
