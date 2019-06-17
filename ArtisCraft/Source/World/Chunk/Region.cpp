#include "Region.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../Renderer/RenderMaster.h"

Region::Region(World & world) : _world(&world)
{
	for (int y = 0; y < 5; y++) {
		_chunks.emplace_back(sf::Vector3i(0, y, 0), world);
		Chunk& chunk = _chunks.back();

		ChunkMeshBuilder meshBuild(chunk);
		meshBuild.build(chunk.mesh);
		chunk.mesh.updateMesh();
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

bool Region::outOfBounds(int x, int y, int z)
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;

	if (x < 0 || y < 0 || z < 0) return true;

	if (y >= _chunks.size() * CHUNK_SIZE) return true;

	return false;

}
