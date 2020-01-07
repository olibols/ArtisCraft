#include "ChunkTools.h"

#include "Chunk.h"

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
