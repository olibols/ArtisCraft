#include "CubeRenderer.h"
#include "../Camera.h"

CubeRenderer::CubeRenderer() : _atlas("ArtisPack")
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

	auto top = _atlas.getTexture({ 0, 0 });
	auto side = _atlas.getTexture({ 0, 0 });
	auto bottom = _atlas.getTexture({ 0, 0 });

	for (auto t : top)
		std::cout << t << std::endl;

	std::vector<GLfloat> texCoords;
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), side.begin(), side.end());
	texCoords.insert(texCoords.end(), top.begin(), top.end());
	texCoords.insert(texCoords.end(), bottom.begin(), bottom.end());

	_quadMesh.textureCoords = texCoords;

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
	_atlas.bindTexture();

	_shader->loadProjViewMatrix(cam.getProjViewMatrix());

	for (auto quad : _quads) {
		_shader->loadModelMatrix(makeModelMatrix(quad, { 0, 0, 0 }));
		glDrawElements(GL_TRIANGLES, _quadModel->getIndicesCount(), GL_UNSIGNED_INT, 0);
	}
	_quads.clear();
}
