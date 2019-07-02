#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"

Chunk::Chunk(sf::Vector3i position, World& world) : _location(position), _world(&world)
{
}

void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBounds(x) ||
		outOfBounds(y) ||
		outOfBounds(z)) return;

	hasMesh = false;
	_blocks[getIndex(x, y ,z)] = block;
}

ChunkBlock Chunk::getBlock(int x, int y, int z)
{
	if (outOfBounds(x) ||
		outOfBounds(y) ||
		outOfBounds(z)) {
	sf::Vector3i location = toWorldPos(x, y, z);
	return _world->getBlock(location.x, location.y, location.z);
	}
	return _blocks[getIndex(x, y, z)];
}

sf::Vector3i Chunk::getLocation()
{
	return _location;
}

void Chunk::buildMesh()
{
	//if (!hasMesh) {
		ChunkMeshBuilder(*this).build();
		mesh.updateMesh();
		hasMesh = true;
	//}

}

sf::Vector3i Chunk::toWorldPos(int x, int y, int z)
{
	sf::Vector3i pos = { 
		_location.x * CHUNK_SIZE + x,
		_location.y * CHUNK_SIZE + y,
		_location.z * CHUNK_SIZE + z,
	};

	return pos;
}

bool Chunk::outOfBounds(int value)
{
	return  value >= CHUNK_SIZE ||
		value < 0;
}

int Chunk::getIndex(int x, int y, int z) // The blocks are stored in a 1D array for speed etc, this func finds the block from 3d coords.
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}
