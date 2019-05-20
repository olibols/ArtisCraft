#include "QuadRenderer.h"
#include "Matrix.h"
#include "../Camera.h"

QuadRenderer::QuadRenderer()
{
	m_texture.loadFromFile("dirt");

	m_quadModel.addData(
		{
			-0.5,  0.5, 0,
			 0.5,  0.5, 0,
			 0.5, -0.5, 0,
			-0.5, -0.5, 0,
		},
	{
		0, 1,
		1, 1,
		1, 0,
		0, 0,
	},
	{
		0, 1, 2,
		2, 3, 0
	});

}

void QuadRenderer::add(glm::vec3 position)
{
	m_quads.push_back(position);
}

void QuadRenderer::renderQuads(Camera camera)
{
	m_shader.useProgram();
	m_quadModel.bindVAO();
	m_texture.bindTexture();

	m_shader.loadProjectionViewMatrix(camera.getProjectionViewMatrix());

	for (auto quad : m_quads) {
		m_shader.loadModelMatrix(makeModelMatrix({ quad, {0, 0, 0} }));

		glDrawElements(GL_TRIANGLES, m_quadModel.getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	m_quads.clear();
}
