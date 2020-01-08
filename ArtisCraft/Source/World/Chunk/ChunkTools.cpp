#include "ChunkTools.h"

#include "Chunk.h"
#include "../Coordinates.h"

void ChunkTools::fillChunk(Chunk & chunk, BlockID block)
{
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				chunk.setBlock(x, y, z, BlockID::Grass);
			}
		}
	}
}

void ChunkTools::fillChunk(Chunk & chunk, WorldTerrain & terrain)
{
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				sf::Vector3i worldPos = toGlobalBlockPos({ x, y, z }, chunk.getLocation());
				if (worldPos.y < 1) {
					chunk.setBlock(x, y, z, BlockID::Grass);
				}
			}
		}
	}
}
