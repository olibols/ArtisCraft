#include "ChunkRenderer.h"
#include "../World/Chunk/ChunkMesh.h"
#include "../World/Block/BlockTypeDatabase.h"
#include "../Camera.h"

void ChunkRenderer::add(ChunkMesh& mesh)
{
	_chunks.push_back(&mesh);
}

void ChunkRenderer::render(Camera& camera)
{
	if (_chunks.empty()) return;

	glDisable(GL_BLEND);
	glDisable(GL_CULL_FACE);

	_shader.useProgram();
	BlockDatabase::get().atlas.bindTexture();

	_shader.loadProjViewMatrix(camera.getProjViewMatrix());

	for (auto* mesh : _chunks) {
		ChunkMesh& model = *mesh;

		model.getModel().bindVAO();
		glDrawElements(GL_TRIANGLES, model.getModel().getIndicesCount(), GL_UNSIGNED_INT, nullptr);
	}

	_chunks.clear();
}
