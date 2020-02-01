#include "ChunkRenderer.h"

void ChunkRenderer::addChunk(ChunkMesh & chunk)
{
	m_chunks.push_back(&chunk);
}

void ChunkRenderer::render(Camera & cam)
{
	m_shader.useProgram();

	m_shader.loadProjViewMatrix(cam.getProjViewMatrix());

	for (auto chunk : m_chunks) {
		chunk->model.bindVAO();
		glDrawElements(GL_TRIANGLES, chunk->model.getIndiceCount(), GL_UNSIGNED_INT, nullptr);
	}
	m_chunks.clear();
}

void ChunkRenderer::clearChunks()
{
	m_chunks.clear();
}
