#include "ChunkRenderer.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../World/Block/BlockTypeDatabase.h"
#include "../Camera.h"

void ChunkRenderer::add(ChunkMesh mesh)
{
	_chunks.push_back(mesh);
}

void ChunkRenderer::render(Camera& camera)
{

	if (_chunks.empty()) return;

	_shader.useProgram();
	BlockDatabase::get().atlas.bindTexture();

	_shader.loadProjViewMatrix(camera.getProjViewMatrix());

	for (ChunkMesh& mesh : _chunks) {

		mesh.getModel().bindVAO();
		glDrawElements(GL_TRIANGLES, mesh.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	_chunks.clear();
}
