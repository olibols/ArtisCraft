#include "ChunkTools.h"

#include "Chunk.h"
#include "../Coordinates.h"

#include <stdio.h>

void ChunkTools::fillChunk(Chunk & chunk, BlockID block)
{
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				chunk.setBlock(x, y, z, block);
			}
		}
	}
}

void ChunkTools::fillChunk(Chunk & chunk, WorldTerrain & terrain)
{
	if (!chunk.isLoaded()) {
		sf::Clock clock;
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					sf::Vector3i worldPos = toGlobalBlockPos({ x, y, z }, chunk.getLocation());
					BlockID block = terrain.getBlockAt(worldPos.x, worldPos.y, worldPos.z);
					if (block == BlockID::Air) break;

					chunk.setBlock(x, y, z, block);
				}
			}
		}
		printf("Took %f seconds to fill chunk! \n", clock.getElapsedTime().asSeconds());
	}
	chunk.setLoaded();
}
