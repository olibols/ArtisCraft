#include "Chunk.h"

Chunk::Chunk(sf::Vector3i pos) : m_location(pos)
{
}

void Chunk::setBlock(int x, int y, int z, BlockID block)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		return;
	}
	m_blocks[getIndex(x, y, z)] = block;
}

BlockID Chunk::getBlock(int x, int y, int z)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		return BlockID::Air;
	}
	return m_blocks[getIndex(x, y, z)];
}

sf::Vector3i Chunk::getLocation()
{
	return m_location;
}

int Chunk::getIndex(int x, int y, int z)
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}

bool Chunk::isOutOfBounds(int index)
{
	return  index >= CHUNK_SIZE || index < 0;
}
