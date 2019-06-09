#include "Section.h"

ChunkSection::ChunkSection()
{

}

void ChunkSection::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBounds(x)) return;
	if (outOfBounds(y)) return;
	if (outOfBounds(z)) return;

	_blocks[getIndex(x, y, z)] = block;
}

ChunkBlock ChunkSection::getBlock(int x, int y, int z)
{
	if (outOfBounds(x)) return BlockID::Air;
	if (outOfBounds(y)) return BlockID::Air;
	if (outOfBounds(z)) return BlockID::Air;

	return _blocks[getIndex(x, y, z)];
}

bool ChunkSection::outOfBounds(int value)
{
	if (value >= CHUNK_SIZE || value < 0) return 0;
	else return 1;
}

int ChunkSection::getIndex(int x, int y, int z)
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
