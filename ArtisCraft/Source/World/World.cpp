#include "World.h"

#include "Chunk/ChunkTools.h"

World::World(Camera& camera) : m_seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), m_worldTerrain(m_seed), m_chunkManager(m_worldTerrain)
{
	m_chunkLoadThread = std::thread([&]() {
		while (true) {
			loadChunks(camera);
		}
	});
}

void World::loadChunks(Camera & camera)
{
	sf::Vector3i pos = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z, });
	bool chunkBuilt = false;
	for (int i = 0; i < m_loadDistance; i++) {
		sf::Vector3i min = {pos.x - i, pos.y - std::max(i/2, 2), pos.z - i};
		sf::Vector3i max = {pos.x + i, pos.y + std::max(i/2, 2), pos.z + i};

		for (int x = min.x; x < max.x; x++) {
			for (int z = min.z; z < max.z; z++) {
				for (int y = min.y; y < max.y; y++) {
					m_mutex.lock();
					auto& chunk = m_chunkManager.addChunk({x,y,z});
					if (!chunk.isLoaded()) {
						m_chunkManager.buildNeighbours(chunk.getLocation(), m_worldTerrain);
						chunk.buildMesh();
						chunkBuilt = true;
					}
					if (!chunk.hasMesh()) {
						chunk.buildMesh();
						chunkBuilt = true;
					}
					m_mutex.unlock();
				}
				if (chunkBuilt) break;
			}
		}
	}
	if(!chunkBuilt)m_loadDistance++;
	if(m_loadDistance >= 8) m_loadDistance = 2;
}

void World::loadChunk(sf::Vector3i pos)
{
	m_worldTerrain.buildChunk(&m_chunkManager.addChunk(pos));
}

void World::render(MasterRenderer & renderer)
{
	for (auto& chunk : m_chunkManager.getChunks()) {
		chunk.second.draw(renderer);
	}
}

void World::setBlock(int x, int y, int z, BlockID block)
{
	m_chunkManager.setBlock({ x,y,z }, block);
}

BlockID World::getBlock(int x, int y, int z)
{
	return m_chunkManager.getBlock({ x,y,z });
}