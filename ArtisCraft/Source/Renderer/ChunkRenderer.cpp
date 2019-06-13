#include "ChunkRenderer.h"
#include "../World/Block/Chunk/ChunkMesh.h"
#include "../World/Block/BlockTypeDatabase.h"
#include "../Camera.h"

void ChunkRenderer::add(ChunkMesh mesh)
{
	_chunks.push_back(mesh);
}

void ChunkRenderer::render(Camera& camera)
{
	_shader.useProgram();
	BlockDatabase::get().atlas.bindTexture();

	_shader.loadProjViewMatrix(camera.getProjViewMatrix());

	for (ChunkMesh mesh : _chunks) {
		ChunkMesh model = mesh;

		model.getModel().bindVAO();
		glDrawElements(GL_TRIANGLES, model.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	_chunks.clear();
}
