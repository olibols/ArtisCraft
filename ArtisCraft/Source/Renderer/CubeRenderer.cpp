#include "CubeRenderer.h"
#include "../Camera.h"

CubeRenderer::CubeRenderer()
{
	_shader = new BlockShader();
	_cubeModel = new Model();
	
	_cubeMesh.vertexPositions = {
		0.5, 0, 0,
		0, 0, 0,
		0, 0, 0,
		0.5, 0.5, 0,

		//Front
		0, 0, 0.5,
		0.5, 0, 0.5,
		0.5, 0.5, 0.5,
		0, 0.5, 0.5,

		//Right
		0.5, 0, 0.5,
		0.5, 0, 0,
		0.5, 0.5, 0,
		0.5, 0.5, 0.5,

		//Left
		0, 0, 0,
		0, 0, 0.5,
		0, 0.5, 0.5,
		0, 0.5, 0,

		//Top
		0, 0.5, 0.5,
		0.5, 0.5, 0.5,
		0.5, 0.5, 0,
		0, 0.5, 0,

		//Bottom
		0, 0, 0,
		0.5, 0, 0,
		0.5, 0, 0.5,
		0, 0, 0.5
	};


	_cubeMesh.indices = {
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

	_cubeModel->addData(_cubeMesh);
}

void CubeRenderer::addCube(glm::vec3 pos) {
	_quads.push_back(pos);
}

void CubeRenderer::renderCubes(Camera& cam)
{
	_shader->useProgram();
	_cubeModel->bindVAO();

	_shader->loadProjViewMatrix(cam.getProjViewMatrix());

	for (auto quad : _quads) {
		_shader->loadModelMatrix(makeModelMatrix({ quad.x, quad.y, quad.z }, { 0, 0, 0 }));
		glDrawElements(GL_TRIANGLES, _cubeModel->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
	_quads.clear();
}
