#include "World.h"

#include "Chunk/ChunkTools.h"

World::World(Camera& camera) : m_worldTerrain(m_seed)
{
	/*m_chunkManagementThread = std::thread([&]()
	{
		while (true) {
			//std::thread chunkload(&World::loadChunks, this, camera);
			std::thread meshbuild(&World::buildChunks, this, camera);

			//std::this_thread::sleep_for(std::chrono::duration(std::chrono::milliseconds(100)));
			//chunkload.join();
			meshbuild.join();
		}
	});*/

	m_meshBuildThread = std::thread([&]() {
		while (true) {
			buildChunks(camera);
		}
	});

	m_chunkLoadThread = std::thread([&]() {
		while (true) {
			loadChunks(camera);
		}
	});

}

void World::loadChunks(Camera & camera)
{
	/*sf::Vector3i pos = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z, });
	bool chunkBuilt = false;
	for (int i = 0; i < m_loadDistance; i++) {
		sf::Vector3i min = {pos.x - i, pos.y - std::max(i/3, 1), pos.z - i};
		sf::Vector3i max = {pos.x + i, pos.y + std::max(i/3, 1), pos.z + i};

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
	if(m_loadDistance >= 16) m_loadDistance = 2;*/
	m_mutex.lock();
	m_chunkManager.updateLoadList(camera);
	
	for (auto& chunk : m_chunkManager.getLoadlist()) {
		ChunkTools::fillChunk(*chunk, m_worldTerrain);
	}
	m_mutex.unlock();
}

void World::buildChunks(Camera & camera)
{
	m_mutex.lock();
	for (auto& chunk : m_chunkManager.getChunks()) {
		if (!chunk.second.hasMesh()) {
			sf::Clock clock;
			chunk.second.buildMesh();
			printf("Took %f seconds to build mesh! \n", clock.getElapsedTime().asSeconds());
		}
	}
	m_mutex.unlock();
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