#include "World.h"
#include "ChunkManager.h"
#include <Utils.h>

constexpr int wsize = 4;
constexpr int renderDistance = 4;


World::World() : _chunkManager(*this)
{
	for (int x = 0; x < wsize; x++)
		for (int z = 0; z < wsize; z++)
			_chunkManager.getRegion(x, z).load();
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

void World::update(const Camera & camera)
{
	for (auto& event : _events) {
		event->handle(*this);
	}
	
	updateRegions();

	bool isMeshMade = false;
	int cameraX = camera.position.x / CHUNK_SIZE;
	int cameraZ = camera.position.z / CHUNK_SIZE;

	for(int i = 0; i < _currentLoadDistance; i++){
		int minX = std::max(cameraX - i, 0);
		int minZ = std::max(cameraZ - i, 0);
		int maxX = cameraX + i;
		int maxZ = cameraZ + i;

		for (int x = minX; x < maxX; ++x) {
			for (int z = minZ; z < maxZ; ++z) {
				if (_chunkManager.makeMesh(x, z)) {
					isMeshMade = true;
					break;
				}
			}
			if (isMeshMade)
				break;
		}
		if (isMeshMade)
			break;
	}

	if (!isMeshMade) _currentLoadDistance++;
	if (_currentLoadDistance >= renderDistance) _currentLoadDistance = 2;


	for (int x = 0; x < wsize; x++) {
		for (int z = 0; z < wsize; z++) {
			if (!_chunkManager.regionExistsAt(x, z)) {
				_chunkManager.loadRegion(x, z);
			}
			_chunkManager.makeMesh(x, z);
		}
	}
	_events.clear();
}

void World::updateRegion(int blockX, int blockY, int blockZ)
{
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

void World::render(RenderMaster & renderer)
{
	auto& regionMap = _chunkManager.getRegions();
	for (auto& region : regionMap) {
		region.second.draw(renderer);
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
	for (auto& region : _regionUpdates) {
		Chunk& section = *region.second;
		section.buildMesh();
	}
	_regionUpdates.clear();
}
