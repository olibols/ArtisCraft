#include "World.h"

World::World()
{
	m_chunkManager.addChunk({ 0, 0, 0 });
	m_chunkManager.addChunk({ 1, 1, 1 });
	m_chunkManager.addChunk({ 1, 0, 1 });

	m_chunkManager.getChunk({ 0, 0, 0 }).buildMesh();
	m_chunkManager.getChunk({ 1, 1, 1 }).buildMesh();
	m_chunkManager.getChunk({ 1, 0, 1 }).buildMesh();
}

void World::render(MasterRenderer & renderer)
{
	for (auto& chunk : m_chunkManager.getChunks()) {
		chunk.second.draw(renderer);
	}
}
