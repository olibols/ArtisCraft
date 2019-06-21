#include "Region.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../Renderer/RenderMaster.h"
#include <time.h>
#include <random>

Region::Region(World & world, sf::Vector2i location) : _world(&world), _location(location)
{
	for (int y = 0; y < 2; y++) {
		_chunks.emplace_back(sf::Vector3i(location.x, y, location.y), world);
	}

	int height = _chunks.size() * CHUNK_SIZE - 20;


	for (int x = 0; x < 16; x++)
	for (int z = 0; z < 16; z++)
	for (int y = 0, srand(sf::Clock()), newh = 10 + rand() % 15; y <= newh; y++)
		{
			if (y == newh) { setBlock(x, y, z, BlockID::Grass); }
			else if (y > newh) { setBlock(x, y, z, BlockID::Dirt); }
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
		meshBuild.build();
		chunk.mesh.updateMesh();
	}
}

void Region::buildMesh(int y)
{
	sf::Clock clok;
	Chunk& chunk = _chunks.at(y / CHUNK_SIZE);
	ChunkMeshBuilder meshBuild(chunk);
	meshBuild.build();
	chunk.mesh.updateMesh();

	printf("Rebuild whole mesh etc in %f seconds \n", clok.getElapsedTime().asSeconds());
}

bool Region::outOfBounds(int x, int y, int z)
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;

	if (x < 0 || y < 0 || z < 0) return true;

	if (y >= (int)_chunks.size() * CHUNK_SIZE) return true;

	return false;

}