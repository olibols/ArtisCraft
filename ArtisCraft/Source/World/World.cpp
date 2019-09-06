#include "World.h"
#include "ChunkManager.h"
#include <Utils.h>

constexpr int wsize = 4;
constexpr int renderDistance = 8;
constexpr int WORKERS = 4;

World::World(Camera& camera) : _chunkManager(*this)
{
	auto seedprep = std::chrono::system_clock::now();
	auto seed = std::chrono::system_clock::to_time_t(seedprep);

	_worldSeed = seed;

	_worldNoise = new NoiseGenerator(seed);

	loadRegions(camera);

	/*for (int i = 0; i < WORKERS; i++)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		_chunkLoadThreads.emplace_back([&]()
		{
			while (_isRunning)
			{
				loadRegions(camera);
				//std::this_thread::sleep_for(std::chrono::microseconds(100));
			}
		});
	}*/
}

ChunkBlock World::getBlock(int x, int y, int z)
{

	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);

	return _chunkManager.getRegion(chunkPos.x, chunkPos.z).getBlock(blockPos.x, y, blockPos.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (y <= 0) return;

	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);
	
	_chunkManager.getRegion(chunkPos.x, chunkPos.z).setBlock(blockPos.x, y, blockPos.z, block);
}

void World::loadRegions(Camera & camera)
{
	bool isMeshMade = false;
	int cameraX = camera.position.x / CHUNK_SIZE;
	int cameraZ = camera.position.z / CHUNK_SIZE;

	for (int i = 0; i < _currentLoadDistance; i++) {
		int minX = std::max(cameraX - i, 0);
		int minZ = std::max(cameraZ - i, 0);
		int maxX = cameraX + i;
		int maxZ = cameraZ + i;

		for (int x = minX; x < maxX; ++x) {
			for (int z = minZ; z < maxZ; ++z) {
				std::lock_guard<std::mutex> mu(_mutex);
				isMeshMade = _chunkManager.makeMesh(x, z);
			}
			//if (isMeshMade)
				//break;
		}
		if (isMeshMade)
			break;
	}

	if (!isMeshMade) _currentLoadDistance++;
	if (_currentLoadDistance >= renderDistance) _currentLoadDistance = 2;

}

void World::update(Camera & camera)
{
	for (auto& event : _events) {
		event->handle(*this);
	}
	_events.clear();

	updateRegions();
	loadRegions(camera);
}

void World::updateRegion(int blockX, int blockY, int blockZ)
{
	//std::lock_guard<std::mutex> mu(_mutex);

	auto addChunkToUpdateBatch = [&](const sf::Vector3i& key, Chunk& chunk)
	{
		_regionUpdates.emplace(key, &chunk);
	};

	auto chunkPos = getChunkXZ(blockX, blockZ);
	auto chunkY = blockY / CHUNK_SIZE;
	
	sf::Vector3i key(chunkPos.x, chunkY, chunkPos.z);
	addChunkToUpdateBatch(key, _chunkManager.getRegion(chunkPos.x, chunkPos.z).getChunk(chunkY));

	auto chunkBlockXZ = getBlockXZ(blockX, blockZ);
	auto chunkBlockY = blockY % CHUNK_SIZE;

	if (chunkBlockXZ.x == 0)
	{
		sf::Vector3i newKey(chunkPos.x - 1, chunkY, chunkPos.z);
		addChunkToUpdateBatch(newKey, _chunkManager.getRegion(newKey.x, newKey.z).getChunk(newKey.y));
	}
	else if (chunkBlockXZ.x == CHUNK_SIZE - 1)
	{
		sf::Vector3i newKey(chunkPos.x + 1, chunkY, chunkPos.z);
		addChunkToUpdateBatch(newKey, _chunkManager.getRegion(newKey.x, newKey.z).getChunk(newKey.y));
	}

	if (chunkBlockY == 0)
	{
		sf::Vector3i newKey(chunkPos.x, chunkY - 1, chunkPos.z);
		addChunkToUpdateBatch(newKey, _chunkManager.getRegion(newKey.x, newKey.z).getChunk(newKey.y));
	}
	else if (chunkBlockY == CHUNK_SIZE - 1)
	{
		sf::Vector3i newKey(chunkPos.x, chunkY + 1, chunkPos.z);
		addChunkToUpdateBatch(newKey, _chunkManager.getRegion(newKey.x, newKey.z).getChunk(newKey.y));
	}

	if (chunkBlockXZ.z == 0)
	{
		sf::Vector3i newKey(chunkPos.x, chunkY, chunkPos.z - 1);
		addChunkToUpdateBatch(newKey, _chunkManager.getRegion(newKey.x, newKey.z).getChunk(newKey.y));
	}
	else if (chunkBlockXZ.z == CHUNK_SIZE - 1)
	{
		sf::Vector3i newKey(chunkPos.x, chunkY, chunkPos.z + 1);
		addChunkToUpdateBatch(newKey, _chunkManager.getRegion(newKey.x, newKey.z).getChunk(newKey.y));
	}

}

void World::render(RenderMaster & renderer, Camera& camera)
{
	//std::lock_guard<std::mutex> mu(_mutex);

	auto& regionMap = _chunkManager.getRegions();
	for (auto iterator = regionMap.begin(); iterator != regionMap.end();) {
		
		Region& region = iterator->second;

		int minX = (camera.position.x / CHUNK_SIZE) - renderDistance;
		int minZ = (camera.position.z / CHUNK_SIZE) - renderDistance;
		int maxX = (camera.position.x / CHUNK_SIZE) + renderDistance;
		int maxZ = (camera.position.z / CHUNK_SIZE) + renderDistance;

		sf::Vector2i location = region.getLocation();

		if (minX > location.x ||
			minZ > location.y ||
			maxZ < location.y ||
			maxX < location.x)
		{
			iterator = regionMap.erase(iterator);
			continue;
		}
		else
		{
			region.draw(renderer);
			iterator++;
		}
	}

}

VectorXZ World::getBlockXZ(int x, int z)
{
	return
	{
		x % CHUNK_SIZE,
		z % CHUNK_SIZE
	};
}

VectorXZ World::getChunkXZ(int x, int z)
{
	return
	{
		x / CHUNK_SIZE,
		z / CHUNK_SIZE
	};
}

void World::updateRegions()
{
	//std::lock_guard<std::mutex> mu(_mutex);
	for (auto& region : _regionUpdates) {
		Chunk& section = *region.second;
		section.buildMesh();
	}
	_regionUpdates.clear();
}
