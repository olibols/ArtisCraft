#include "World.h"

#include "Chunk/ChunkTools.h"

World::World(Camera& camera) : m_seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), m_worldTerrain(m_seed), m_chunkManager(m_worldTerrain)
{
	loadChunks(camera);
	m_currentChunk = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z });

	m_chunkLoadThread = std::thread([&]() {
		while (true) {
			loadChunks(camera);
		}
	});

	/*m_chunkUpdateThread = std::thread([&]() {
		while (true) {
			processUpdates();
		}
	});*/
}

void World::loadChunks(Camera & camera)
{
	processUpdates();

	if (m_currentChunk != toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z })) {
		m_currentChunk = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z });
		m_loadDistance = 2;
	}

	sf::Vector3i pos = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z, });
	bool chunkBuilt = false;
	for (int i = 0; i < m_loadDistance; i++) {
		sf::Vector3i min = {pos.x - i, pos.y - std::max(i/2, 2), pos.z - i};
		sf::Vector3i max = {pos.x + i, pos.y + std::max(i/2, 2), pos.z + i};

			for (int y = min.y; y < max.y; y++){
				for (int x = min.x; x < max.x; x++){
					for (int z = min.z; z < max.z; z++) {
					m_mutex.lock();
					auto& chunk = m_chunkManager.addChunk({x,y,z});
					m_chunkManager.buildNeighbours({ x,y,z }, m_worldTerrain);
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

void World::processUpdates()
{
	m_mutex.lock();
	for (auto& chunk : m_chunkUpdates) {
		chunk->buildMesh();
	}
	m_chunkUpdates.clear();
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

void World::psetBlock(int x, int y, int z, BlockID block)
{
	m_chunkManager.setBlock({ x,y,z }, block);
	sf::Vector3i chunkPos = toChunkPos({ x,y,z });
	m_chunkUpdates.push_back(&m_chunkManager.getChunk(chunkPos));
}

BlockID World::getBlock(int x, int y, int z)
{
	return m_chunkManager.getBlock({ x,y,z });
}