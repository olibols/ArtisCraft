#include "World.h"

#include "Chunk/ChunkTools.h"

World::World(Camera& camera)
{
	m_chunkManagementThread = std::thread([&]()
	{
		while (true) {
			std::thread chunkload(&World::loadChunks, this, camera);
			std::thread meshbuild(&World::buildChunks, this, camera);

			//std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(100)));
			chunkload.join();
			meshbuild.join();
		}
	});
}

void World::loadChunks(Camera & camera)
{
	sf::Vector3i pos = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z, });
	bool chunkBuilt = false;
	for (int i = 1; i < m_loadDistance; i++) {
		sf::Vector3i min = {pos.x - i, pos.y - std::max(i/2, 1), pos.z - i};
		sf::Vector3i max = {pos.x + i, pos.y + std::max(i/2, 1), pos.z + i};

		for (int x = min.x; x < max.x; x++) {
			for (int y = min.y; y < max.y; y++) {
				for (int z = min.z; z < max.z; z++) {
					m_mutex.lock();
					auto& chunk = m_chunkManager.addChunk({x,y,z});
					if (!chunk.isLoaded()) {
						ChunkTools::fillChunk(chunk, m_worldTerrain);
						chunkBuilt = true;
					}
					m_mutex.unlock();
				}
				if (chunkBuilt) break;
			}
		}
	}
	if(!chunkBuilt)m_loadDistance++;
	if(m_loadDistance >= 16) m_loadDistance = 2;
}

void World::buildChunks(Camera & camera)
{
	for (auto& chunk : m_chunkManager.getChunks()) {
		m_mutex.lock();
		if (!chunk.second.hasMesh()) {
			chunk.second.buildMesh();
		}
		m_mutex.unlock();
	}
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