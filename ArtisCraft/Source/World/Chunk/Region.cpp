#include "Region.h"
#include "ChunkMeshBuilder.h"
#include "../World.h"
#include "../../Renderer/RenderMaster.h"
#include <time.h>
#include <random>
#include <PerlinNoise.h>

Region::Region(World & world, sf::Vector2i location) : _world(&world), _location(location)
{
}

void Region::setBlock(int x, int y, int z, ChunkBlock block)
{
	//addChunkBlockTarget(y);
	if (outOfBounds(x, y, z)) return;

	int blockY = y % CHUNK_SIZE;

	_chunks[y / CHUNK_SIZE].setBlock(x, blockY, z, block);
}

ChunkBlock Region::getBlock(int x, int y, int z)
{
	if (outOfBounds(x, y, z)) return ChunkBlock(BlockID::Air);

	int blockY = y % CHUNK_SIZE;

	return _chunks[y / CHUNK_SIZE].getBlock(x, blockY, z);
}

void Region::draw(RenderMaster & renderer)
{
	for (auto& chunk : _chunks) {
		if (chunk.hasMesh && chunk.hasFaces()) {
			renderer.drawChunk(chunk._mesh);
		}
	}
}

void Region::load()
{
	if (!isLoaded) {
		for (int y = 0; y < 16; y++) {
			_chunks.emplace_back(sf::Vector3i(_location.x, y, _location.y), *_world);
		}

		//siv::PerlinNoise noise(120);

		int height = 8;

		for (int x = 0; x < 16; x++)
			for (int z = 0; z < 16; z++)
				for (int y = 0; y < 16; y++)
				{

					/*double newx = (x + _location.x) / 10.0f;
					double newz = (z + _location.y) / 10.0f;

					int height = noise.noise0_1(newx, newz) * 20 + 5;


					for (int newy = 0; newy <= height; newy++) {
						if (newy == height) { setBlock(x, newy, z, BlockID::Grass); }
						else if (newy > height - 5) { setBlock(x, newy, z, BlockID::Dirt); }
						else { setBlock(x, newy, z, BlockID::Stone); }
					}*/

					

					if (y == height) { setBlock(x, y, z, BlockID::Grass); }
					else if (y < height) { setBlock(x, y, z, BlockID::Dirt); }
					else if(y < height - 6) { setBlock(x, y, z, BlockID::Stone); }

				}

		isLoaded = true;
	}
}

bool Region::buildMesh()
{
	for (auto& chunk : _chunks) {
		if (!chunk.hasMesh && chunk.hasBlocks()) {
			chunk.buildMesh();
			return true;
		}
	}

	return false;
}

Chunk & Region::getChunk(int chunkIndex)
{

	static Chunk errorChunk({ 999,999,999 }, *_world);

	if (chunkIndex >= _chunks.size() || chunkIndex < 0) return errorChunk;

	return _chunks[chunkIndex];
}

void Region::addChunk()
{
	int y = _chunks.size();
	_chunks.emplace_back(sf::Vector3i(_location.x, y, _location.y), *_world);
}

void Region::addChunkBlockTarget(int blockY)
{
	int index = blockY / CHUNK_SIZE;

	addChunkIndexTarget(index);
}

void Region::addChunkIndexTarget(int index)
{
	while (_chunks.size() < index - 1) {
		addChunk();
	}
}

bool Region::outOfBounds(int x, int y, int z)
{
	if (x >= CHUNK_SIZE) return true;
	if (z >= CHUNK_SIZE) return true;

	if (x < 0 || y < 0 || z < 0) return true;

	if (y >= CHUNK_AREA) return true;

	return false;

}