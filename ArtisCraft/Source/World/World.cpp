#include "World.h"
#include <Utils.h>

constexpr int wsize = 2;

World::World()
{
	for (int x = 0; x < wsize; x++)
		for (int z = 0; z < wsize; z++)
			_regions.emplace_back(*this, sf::Vector2i(x, z));

	for (auto& region : _regions)
		region.buildMesh();
}

ChunkBlock World::getBlock(int x, int y, int z)
{

	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);

	if (isOutOfBounds(chunkPos)) return BlockID::Air;

	return _regions.at(chunkPos.x * wsize + chunkPos.z).getBlock(blockPos.x, y, blockPos.z);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{

	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);

	if (isOutOfBounds(chunkPos)) return;

	_regions.at(chunkPos.x * wsize + chunkPos.z).setBlock(blockPos.x, y, blockPos.z, block);
}

void World::editBlock(int x, int y, int z, ChunkBlock block)
{
	VectorXZ blockPos = getBlockXZ(x, z);
	VectorXZ chunkPos = getChunkXZ(x, z);

	if (isOutOfBounds(chunkPos)) return;

	setBlock(x, y, z, block);

	_changedRegions.push_back(&_regions.at(chunkPos.x * wsize + chunkPos.z));
}

void World::rebuildAll()
{
	for (auto& region : _regions) {
		region.buildMesh();
	}
}

void World::render(RenderMaster & renderer)
{
	for (auto& region : _changedRegions) {
		region->buildMesh();
	}
	_changedRegions.clear();

	for (auto& region : _regions){
		region.draw(renderer);
	}
}
