#include "CubeRenderer.h"
#include "../Camera.h"

CubeRenderer::CubeRenderer()
{
	_shader = new BlockShader();
	_quadModel = new Model();

	_texture = new BasicTexture("dirt");

	
	_quadMesh.vertexPositions = {
		//Back
		1, 0, 0,
		0, 0, 0,
		0, 1, 0,
		1, 1, 0,

		//Front
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,

		//Right
		1, 0, 1,
		1, 0, 0,
		1, 1, 0,
		1, 1, 1,

		//Left
		0, 0, 0,
		0, 0, 1,
		0, 1, 1,
		0, 1, 0,

		//Top
		0, 1, 1,
		1, 1, 1,
		1, 1, 0,
		0, 1, 0,

		//Bottom
		0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1.
	};

	_quadMesh.textureCoords = {
		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,

		0, 1,
		1, 1,
		1, 0,
		0, 0,
	};

	_quadMesh.indices = {
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

	_quadModel->addData(_quadMesh);
}

void CubeRenderer::addCube(glm::vec3 pos) {
	_quads.push_back(pos);
}

void CubeRenderer::renderCubes(Camera& cam)
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
