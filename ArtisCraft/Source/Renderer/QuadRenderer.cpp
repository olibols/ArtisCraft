#include "QuadRenderer.h"
#include "../Camera.h"

QuadRenderer::QuadRenderer()
{
	_shader = new BlockShader();
	_quadModel = new Model();

	_texture = new BasicTexture("dirt");

	
	_quadMesh.vertexPositions = {
		-0.5,  0.5, 0,
		 0.5,  0.5, 0,
		 0.5, -0.5, 0,
		-0.5, -0.5, 0,
	};

	_quadMesh.textureCoords = {
		0, 1,
		1, 1,
		1, 0,
		0, 0
	};

	_quadMesh.indices = {
		0, 1, 2,
		2, 3, 0
	};

	_quadModel->addData(_quadMesh);
}

void QuadRenderer::addQuad(glm::vec3 pos) {
	_quads.push_back(pos);
}

void QuadRenderer::renderQuads(Camera& cam)
{
	_shader->useProgram();
	_quadModel->bindVAO();
	_texture->bindTexture();

	_shader->loadProjViewMatrix(cam.getProjViewMatrix());

	for (auto quad : _quads) {
		_shader->loadModelMatrix(makeModelMatrix(quad, { 0, 0, 0 }));
		glDrawElements(GL_TRIANGLES, _quadModel->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
	_quads.clear();
}
