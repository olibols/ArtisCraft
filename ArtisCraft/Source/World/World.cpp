#include "World.h"

#include "Chunk/ChunkTools.h"

World::World(Camera& camera) : m_seed(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), m_worldTerrain(m_seed, &m_chunkManager), m_chunkManager(m_worldTerrain)
{
	loadChunks(camera);
	m_currentChunk = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z });

	m_chunkLoadThread = std::thread([&]() {
		while (true) {
			loadChunks(camera);
		}
	});
}

void World::loadChunks(Camera & camera)
{
	if (m_currentChunk != toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z })) {
		m_currentChunk = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z });
		m_loadDistance = 0;
	}

	sf::Vector3i pos = toChunkPos({ (int)camera.position.x, (int)camera.position.y, (int)camera.position.z, });
	bool chunkBuilt = false;
	for (int i = 0; i < m_loadDistance; i++) {
		sf::Vector3i min = {pos.x - i, pos.y - std::max(i/2, 0), pos.z - i};
		sf::Vector3i max = {pos.x + i, pos.y + std::max(i/2, 0), pos.z + i};

			for (int y = min.y; y < max.y; y++){
				for (int x = min.x; x < max.x; x++){
					for (int z = min.z; z < max.z; z++) {
						processUpdates();
						m_mutex.lock();
						m_mapChanged = true;
						auto& chunk = m_chunkManager.addChunk({x,y,z});
						m_chunkManager.buildNeighbours({ x,y,z }, m_worldTerrain);
						m_mutex.unlock();
						if (!chunk.isSeeded()) {
							m_worldTerrain.seedChunk(&chunk);
						}
						if (!chunk.hasMesh()) {
							m_mutex.lock();
							chunk.buildMesh();
							m_mutex.unlock();
							chunkBuilt = true;
						}
				}
				if (chunkBuilt) break;
			}
		}
	}
	if(!chunkBuilt)m_loadDistance++;
	if(m_loadDistance >= 8) m_loadDistance = 0;
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
	try
	{
		for (auto& chunk : m_chunkManager.getChunks()) {
			chunk.second.draw(renderer);
		}
	}
	catch (const std::exception&){}
}

void World::setBlock(int x, int y, int z, BlockID block)
{
	m_chunkManager.setBlock({ x,y,z }, block);
}

void World::psetBlock(int x, int y, int z, BlockID block)
{
	m_chunkManager.setBlock({ x,y,z }, block);
	updateChunk(x, y, z);
}

void World::updateChunk(int x, int y, int z)
{
	sf::Vector3i chunkPos = toChunkPos({ x,y,z });
	sf::Vector3i localPos = toLocalBlockPos({ x,y,z });

	m_chunkUpdates.push_back(&m_chunkManager.getChunk(chunkPos));

	if (localPos.x == 0) m_chunkUpdates.push_back(&m_chunkManager.getChunk({ chunkPos.x - 1, chunkPos.y, chunkPos.z }));
	if (localPos.y == 0) m_chunkUpdates.push_back(&m_chunkManager.getChunk({ chunkPos.x, chunkPos.y - 1, chunkPos.z }));
	if (localPos.z == 0) m_chunkUpdates.push_back(&m_chunkManager.getChunk({ chunkPos.x, chunkPos.y, chunkPos.z - 1 }));

	if (localPos.x == CHUNK_SIZE - 1) m_chunkUpdates.push_back(&m_chunkManager.getChunk({ chunkPos.x + 1, chunkPos.y, chunkPos.z }));
	if (localPos.y == CHUNK_SIZE - 1) m_chunkUpdates.push_back(&m_chunkManager.getChunk({ chunkPos.x, chunkPos.y + 1, chunkPos.z }));
	if (localPos.z == CHUNK_SIZE - 1) m_chunkUpdates.push_back(&m_chunkManager.getChunk({ chunkPos.x, chunkPos.y, chunkPos.z + 1 }));
}

BlockID World::getBlock(int x, int y, int z)
{
	return m_chunkManager.getBlock({ x,y,z });
}

int World::getHeight(int x, int z)
{
	return m_worldTerrain.getHeightAt(x, z);
}
