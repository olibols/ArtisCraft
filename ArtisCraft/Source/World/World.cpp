#include "World.h"
#include "ChunkManager.h"
#include <Utils.h>

std::unordered_set<sf::Vector3i> World::_changedRegions;

constexpr int wsize = 5;

bool isOutOfBounds(VectorXZ regionPosition) {
	if (regionPosition.x < 0) return true;
	if (regionPosition.z < 0) return true;
	if (regionPosition.x >= wsize) return true;
	if (regionPosition.z >= wsize) return true;
	return false;
}

World::World() : _chunkManager(*this)
{
	for (int x = 0; x < wsize; x++)
		for (int z = 0; z < wsize; z++)
			_chunkManager.getRegion(x, z).load();



	for (int x = 0; x < wsize; x++) {
		for (int z = 0; z < wsize; z++) {
			_chunkManager.makeMesh(x, z);
		}
	}
}

ChunkBlock World::getBlock(int x, int y, int z)
{

	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);

	if (isOutOfBounds(chunkPos)) return BlockID::Air;

	return _chunkManager.getRegion(chunkPos.x, chunkPos.z).getBlock(blockPos.x, y, blockPos.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (y == 0) return;

	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);

	if (isOutOfBounds(chunkPos)) return;
	
	auto& region = _chunkManager.getRegion(chunkPos.x, chunkPos.z);
	region.setBlock(blockPos.x, y, blockPos.z, block);
	if (region.hasLoaded())
	{
		_changedRegions.emplace(chunkPos.x, y / CHUNK_SIZE, chunkPos.z);
	}
}

void World::render(RenderMaster & renderer)
{
	for (auto& location : _changedRegions) {
		try {
			Chunk& chunk = _chunkManager.getRegion(location.x, location.z).getChunk(location.y);
			chunk.buildMesh();
		}
		catch(std::exception e){}
	}

	_changedRegions.clear();

	auto& regions = _chunkManager.getRegions();

	for (auto& region : regions) {
		region.second.draw(renderer);
	}
}
