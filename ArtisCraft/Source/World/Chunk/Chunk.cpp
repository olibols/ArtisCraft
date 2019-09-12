#include "Chunk.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"

Chunk::Chunk(sf::Vector3i position, World& world) : _location(position), _world(&world)
{
	memset(_lightMap, 0, sizeof(_lightMap));
}

void Chunk::setBlock(int x, int y, int z, ChunkBlock block)
{
	if (outOfBounds(x) ||
		outOfBounds(y) ||
		outOfBounds(z)) 
	{
		auto location = toWorldPos(x, y, z);
		_world->setBlock(location.x, location.y, location.z, block);
		return;
	};

	if (block == BlockID::Water) {

		setBlockLight(x, y, z, 12);
		short index = y * CHUNK_AREA + z * CHUNK_SIZE + x;

		_lightNodeQueue.emplace(index, this);
	}
	
	fillLight();

	_blocks[getIndex(x, y, z)] = block;
	_layers[y].update(block);

}

void Chunk::fillLight()
{

	while (_lightNodeQueue.empty() == false) {

		LightNode& node = _lightNodeQueue.front();

		short index = node.index;
		Chunk* chunk = node.chunk;

		_lightNodeQueue.pop();

		int x = index % CHUNK_SIZE;
		int y = index / (CHUNK_SIZE * CHUNK_SIZE);
		int z = (index % (CHUNK_SIZE * CHUNK_SIZE)) / CHUNK_SIZE;

		int lightLevel = chunk->getBlocklight(x, y, z);

		if (chunk->getBlock(x + 1, y, z) != BlockID::Air && chunk->getBlocklight(x + 1, y, z) + 2 <= lightLevel) {

			chunk->setBlockLight(x + 1, y, z, lightLevel - 1);

			short index = y * CHUNK_AREA + z * CHUNK_SIZE + x + 1;

			_lightNodeQueue.emplace(index, chunk);
		}
	}
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

bool Chunk::hasFaces()
{
	if (_mesh.hasMesh()) return true;
	else return false;
}

void Chunk::buildMesh()
{
	ChunkMeshBuilder(*this).build();
	_hasMeshBuffered = false;
	_hasMesh = true;
}

void Chunk::bufferMesh() {
	_mesh.updateMesh();
	_hasMeshBuffered = true;
}

ChunkLayer & Chunk::getLayer(int y)
{
	if (y == -1) {
		return _world->getChunkManager().getRegion(_location.x, _location.z).getChunk(_location.y - 1).getLayer(CHUNK_SIZE - 1);
	}
	else if(y == CHUNK_SIZE){
		return _world->getChunkManager().getRegion(_location.x, _location.z).getChunk(_location.y + 1).getLayer(0);
	}
	else {
		return _layers[y];
	}
}

Chunk & Chunk::getAdjacentChunk(int x, int z)
{
	return _world->getChunkManager().getRegion(_location.x + x, _location.z + z).getChunk(_location.y);
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
