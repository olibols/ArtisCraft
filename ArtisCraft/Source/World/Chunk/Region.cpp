#include "Region.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../Renderer/RenderMaster.h"
#include <time.h>

Region::Region(World & world, sf::Vector2i location) : _world(&world), _location(location)
{
	for (int y = 0; y < 2; y++) {
		_chunks.emplace_back(sf::Vector3i(location.x, y, location.y), world);
	}

	int height = _chunks.size() * CHUNK_SIZE - 1;

	for (int y = 0; y < _chunks.size() * CHUNK_SIZE; y++)
		for (int x = 0; x < 16; x++)
			for (int z = 0; z < 16; z++)
			{
				if (y == height) { setBlock(x, y, z, BlockID::Grass); }
				else if (y > height - 3) { setBlock(x, y, z, BlockID::Dirt); }
				else { setBlock(x, y, z, BlockID::Stone); }
			}

}

void Region::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBounds(x, y, z)) return;

	int blockY = y % CHUNK_SIZE;

	_chunks.at(y / CHUNK_SIZE).setBlock(x, blockY, z, block);

}

ChunkBlock Region::getBlock(int x, int y, int z)
{
	if (outOfBounds(x, y, z)) return ChunkBlock(BlockID::Air);

	int blockY = y % CHUNK_SIZE;

	return _chunks.at(y / CHUNK_SIZE).getBlock(x, blockY, z);
}

void Region::draw(RenderMaster & renderer)
{
	for (auto& chunk : _chunks) {
		renderer.drawChunk(chunk.mesh);
	}
}

void Region::buildMesh()
{
	for (auto& chunk : _chunks) {
		ChunkMeshBuilder meshBuild(chunk);
		meshBuild.build(chunk.mesh);
		chunk.mesh.updateMesh();
	}
}

bool Region::outOfBounds(int x, int y, int z)
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;

	if (x < 0 || y < 0 || z < 0) return true;

	if (y >= (int)_chunks.size() * CHUNK_SIZE) return true;

	return false;

}