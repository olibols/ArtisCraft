#include "World.h"

World::World(Camera& camera)
{
	for (int x = -2; x < 2; x++) {
		for (int y = -2; y < 2; y++) {
			for (int z = -2; z < 2; z++) {
				m_chunkManager.addChunk({ x,y,z });
			}
		}
	}
	
	for (int i = 0; i < 4; i++) {
		m_meshBuildThreads.emplace_back([&]()
		{
			loadChunks(camera);
		});
	}
}

void World::loadChunks(Camera & camera)
{
	for (int x = -2; x < 2; x++) {
		for (int y = -2; y < 2; y++) {
			for (int z = -2; z < 2; z++) {
				m_mutex.lock();
				if (!m_chunkManager.getChunk({ x,y,z }).hasMesh()) {
					m_chunkManager.getChunk({ x,y,z }).buildMesh();
				}
				m_mutex.unlock();
			}
		}
	}
}

void World::render(MasterRenderer & renderer)
{
	for (auto& chunk : m_chunkManager.getChunks()) {
		chunk.second.draw(renderer);
	}
}
