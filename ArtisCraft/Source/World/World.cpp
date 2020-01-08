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
	for(int x = pos.x - 2; x < pos.x + 2; x++)
		for(int y = pos.y - 2; y < pos.y + 2; y++)
			for (int z = pos.z - 2; z < pos.z + 2; z++) {
				auto& chunk = m_chunkManager.addChunk({ x,y,z });
				if (!chunk.isLoaded()) {
					ChunkTools::fillChunk(chunk, m_worldTerrain);
					chunk.setLoaded();
				}
	}
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