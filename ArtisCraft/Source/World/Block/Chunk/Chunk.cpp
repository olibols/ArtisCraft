#include "Chunk.h"

Chunk::Chunk()
{
	_location = { 0, 0, 0 };

	for (int i = 0; i < CHUNK_VOLUME; i++) {
		_blocks[i] = ChunkBlock(BlockID::Dirt);
	}

}

void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBounds(x, y, z)) return;

	_blocks[getIndex(x, y ,z)] = block;
}

ChunkBlock Chunk::getBlock(int x, int y, int z)
{
	if (outOfBounds(x, y, z)) return BlockID::Air;

	return _blocks[getIndex(x, y, z)];
}

sf::Vector3i Chunk::getLocation()
{
	return _location;
}

bool Chunk::outOfBounds(int x, int y, int z)
{
	if (x >= CHUNK_SIZE || y >= CHUNK_SIZE || z >= CHUNK_SIZE) return true;
	if (x < 0 || y < 0 || z < 0) return true;
	
	return false;
}

int Chunk::getIndex(int x, int y, int z) // The blocks are stored in a 1D array for speed etc, this func finds the block from 3d coords.
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
