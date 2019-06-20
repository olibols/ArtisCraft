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
	int bX = x % CHUNK_SIZE;
	int bZ = z % CHUNK_SIZE;

	int cX = x / CHUNK_SIZE;
	int cZ = z / CHUNK_SIZE;

	if (cX < 0) return ChunkBlock(BlockID::Air);
	if (cZ < 0) return ChunkBlock(BlockID::Air);
	if (cX >= wsize) return ChunkBlock(BlockID::Air);
	if (cZ >= wsize) return ChunkBlock(BlockID::Air);

	return _regions.at(cX * wsize + cZ).getBlock(bX, y, bZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{

	int bX = x % CHUNK_SIZE;
	int bZ = z % CHUNK_SIZE;

	int cX = x / CHUNK_SIZE;
	int cZ = z / CHUNK_SIZE;

	if (cX < 0) return;
	if (cZ < 0) return;
	if (cX >= wsize) return;
	if (cZ >= wsize) return;

	_regions.at(cX * wsize + cZ).setBlock(bX, y, bZ, block);
}

void World::editBlock(int x, int y, int z, ChunkBlock block)
{
	int cX = x / CHUNK_SIZE;
	int cZ = z / CHUNK_SIZE;

	if (cX < 0) return;
	if (cZ < 0) return;
	if (cX >= wsize) return;
	if (cZ >= wsize) return;

	setBlock(x, y, z, block);

	_regions.at(cX * wsize + cZ).buildMesh();
}

void World::rebuildAll()
{
	for (auto& region : _regions) {
		region.buildMesh();
	}
}

void World::render(RenderMaster & renderer)
{
	for (auto& region : _regions) {
		region.draw(renderer);
		//region.buildMesh();
	}
}
