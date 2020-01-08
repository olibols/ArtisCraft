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

				BlockID block = chunk.getBlock(x, y, z);

				if (block != BlockID::Air) {

					BlockID checkblock = chunk.getBlock(x - 1, y, z);
					if (checkblock == BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::LEFT_FACE, BlockTypeDatabase::get().getColor(block) * glm::vec3(0.8) }, { x, y, z });
					}

					checkblock = chunk.getBlock(x + 1, y, z);
					if (checkblock == BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::RIGHT_FACE, BlockTypeDatabase::get().getColor(block) * glm::vec3(0.8) }, { x, y, z });
					}

					checkblock = chunk.getBlock(x, y, z + 1);
					if (checkblock == BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::FRONT_FACE, BlockTypeDatabase::get().getColor(block) * glm::vec3(0.6) }, { x, y, z });
					}

					checkblock = chunk.getBlock(x, y, z - 1);
					if (checkblock == BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::BACK_FACE, BlockTypeDatabase::get().getColor(block) * glm::vec3(0.6) }, { x, y, z });
					}

					checkblock = chunk.getBlock(x, y + 1, z);
					if (checkblock == BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::TOP_FACE, BlockTypeDatabase::get().getColor(block) }, { x, y, z });
					}

					checkblock = chunk.getBlock(x, y - 1, z);
					if (checkblock == BlockID::Air) {
						chunkmesh.addFace({ QuadPrimitive::BOTTOM_FACE, BlockTypeDatabase::get().getColor(block) * glm::vec3(0.4) }, { x, y, z });
					}
				}
			}
		}
	}

	return chunkmesh;
}
