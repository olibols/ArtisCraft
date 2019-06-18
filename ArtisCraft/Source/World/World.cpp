#include "World.h"

World::World() : _region(*this)
{}

ChunkBlock World::getBlock(int x, int y, int z)
{
	int blockX = x % CHUNK_SIZE;
	int blockY = y % CHUNK_SIZE;
	int blockZ = z % CHUNK_SIZE;

	return _region.getBlock(blockX, blockY, blockZ);
}

void World::setBlock(int x, int y, int z, ChunkBlock block)
{
}

void World::render(RenderMaster & renderer)
{
	_region.draw(renderer);
}
