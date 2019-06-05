#include "QuadRenderer.h"
#include <Matrix.h>
#include "../Camera.h"

QuadRenderer::QuadRenderer()
{
	_shader = new BlockShader;
	_texture = new BasicTexture("dirt");
	_quadModel = new Model();

	Mesh mesh;
	mesh.vertexPositions = {
		-0.5,  0.5, 0,
		0.5,  0.5, 0,
		0.5, -0.5, 0,
		-0.5, -0.5, 0,
	};

	mesh.textureCoords = {
		0, 1,
		1, 1,
		1, 0,
		0, 0
	};

	mesh.indices = {
		0, 1, 2,
		2, 3, 0
	};

	_quadModel->addData(mesh);
}

void QuadRenderer::addQuad(const glm::vec3 pos)
{
	_quads.push_back(pos);
}

void QuadRenderer::render(const Camera & camera)
{
	_shader->useProgram();
	_quadModel->bindVAO();
	_texture->bindTexture();

	_shader->loadProjViewMatrix(camera.getProjViewMatrix());

	for (auto& quad : _quads) {
		_shader->loadModelMatrix(makeModelMatrix({ quad, {0, 0, 0} }));
	}

}
