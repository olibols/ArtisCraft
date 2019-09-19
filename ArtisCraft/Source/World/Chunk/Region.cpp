#include "Region.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../Renderer/RenderMaster.h"
#include <time.h>
#include <random>

Region::Region(World & world, sf::Vector2i location) : _world(&world), _location(location)
{
}

void Region::setBlock(int x, int y, int z, ChunkBlock block)
{
	//addChunkBlockTarget(y);
	if (outOfBounds(x, y, z)) return;

	int blockY = y % CHUNK_SIZE;

	_chunks[y / CHUNK_SIZE].setBlock(x, blockY, z, block);
}

ChunkBlock Region::getBlock(int x, int y, int z)
{
	if (outOfBounds(x, y, z)) return ChunkBlock(BlockID::Air);

	int blockY = y % CHUNK_SIZE;

	return _chunks[y / CHUNK_SIZE].getBlock(x, blockY, z);
}

void Region::draw(RenderMaster & renderer)
{
	for (auto& chunk : _chunks) {
		if (chunk.hasMesh()) {
			if (!chunk.hasBuffered())
				chunk.bufferMesh();

			renderer.drawChunk(chunk.getMesh());
		}
	}
}

void Region::load(WorldTerrain& worldTerrain)
{

	if (!_isLoaded) {
		for (int y = 0; y < 32; y++) {
			_chunks.emplace_back(sf::Vector3i(_location.x, y, _location.y), *_world);
		}

		worldTerrain.generateTerrainFor(*this);

		_isLoaded = true;
	}
}

bool Region::buildMesh()
{
	for (auto& chunk : _chunks) {
		if (!chunk.hasMesh()) {
			chunk.buildMesh();
			return true;
		}
	}

	return false;
}

Chunk & Region::getChunk(int chunkIndex)
{

	static Chunk errorChunk({ 999,999,999 }, *_world);

	if (chunkIndex >= _chunks.size() || chunkIndex < 0) return errorChunk;

	return _chunks[chunkIndex];
}

void Region::addChunk()
{
	int y = _chunks.size();
	_chunks.emplace_back(sf::Vector3i(_location.x, y, _location.y), *_world);
}

void Region::addChunkBlockTarget(int blockY)
{
	int index = blockY / CHUNK_SIZE;

	addChunkIndexTarget(index);
}

void Region::addChunkIndexTarget(int index)
{
	while (_chunks.size() < index - 1) {
		addChunk();
	}
}

bool Region::outOfBounds(int x, int y, int z)
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;

	if (x < 0 || y < 0 || z < 0) return true;

	if (y >= CHUNK_AREA) return true;

	return false;

}