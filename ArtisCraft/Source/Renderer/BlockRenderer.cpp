#include "BlockRenderer.h"
#include "../GL/CubePrimitive.h"

BlockRenderer::BlockRenderer()
{
	Mesh mesh;
	mesh.vertexPositions = primitives::CubeVertexes;
	mesh.indices = primitives::CubeIndices;
	mesh.vertexColors = primitives::createCubeColors({ 1.0, 1.0, 0.5 });

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
	}

	m_positions.clear();
}
