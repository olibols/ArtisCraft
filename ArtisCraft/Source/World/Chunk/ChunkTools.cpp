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
	if (!chunk.isLoaded()) {
		for (int y = 0; y < CHUNK_SIZE; y++) {
			for (int z = 0; z < CHUNK_SIZE; z++) {
				for (int x = 0; x < CHUNK_SIZE; x++) {
					sf::Vector3i worldPos = toGlobalBlockPos({ x, y, z }, chunk.getLocation());
					chunk.setBlock(x, y, z, terrain.getBlockAt(worldPos.x, worldPos.y, worldPos.z));
				}
			}
		}
	}
	chunk.setLoaded();
}
