#include "ChunkMeshBuilder.h"

#include "../../GL/QuadPrimitive.h"
#include "ChunkMesh.h"
#include "Chunk.h"
#include "../BlockTypeDatabase.h"

ChunkMesh buildChunkMesh(Chunk & chunk)
{
	ChunkMesh chunkmesh;
	chunkmesh.worldPos = chunk.getLocation();

	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {

				if (chunk.getBlock(x, y, z) == BlockID::Air) {
					BlockID block;

					block = chunk.getBlock(x - 1, y, z);
					if (block != BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::LEFT_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}

					block = chunk.getBlock(x + 1, y, z);
					if (block != BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::RIGHT_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}

					block = chunk.getBlock(x, y, z + 1);
					if (block != BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::FRONT_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}

					block = chunk.getBlock(x, y, z - 1);
					if (block != BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::BACK_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}

					block = chunk.getBlock(x, y + 1, z);
					if (block != BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::TOP_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}

					block = chunk.getBlock(x, y - 1, z);
					if (block != BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::BOTTOM_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}
				}
			}
		}
	}

	return chunkmesh;
}
