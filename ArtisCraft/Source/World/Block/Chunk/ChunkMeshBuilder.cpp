#include "ChunkMeshBuilder.h"
#include <Utils.h>
#include "../BlockTypeDatabase.h"

ChunkMeshBuilder::ChunkMeshBuilder(Chunk & chunk)
{
	_chunk = &chunk;
}

void ChunkMeshBuilder::build(ChunkMesh & mesh)
{
	_mesh = &mesh;

	AdjacentPositions directions;

	for (int x = 0; x < CHUNK_SIZE; ++x) {
		for (int y = 0; y < CHUNK_SIZE; ++y) {
			for (int z = 0; z < CHUNK_SIZE; ++z) {
				sf::Vector3i position(x, y, z);

				ChunkBlock block = _chunk->getBlock(x, y, z);

				_texData = &BlockDatabase::get().getData((BlockID)block.id).getTextureData();

				auto data = *_texData;
				directions.update(x, y, z);

				auto texCoords = BlockDatabase::get().atlas.getTexture(_texData->texTopCoord);

				_mesh->addBlock(texCoords, _chunk->getLocation(), { x, y, z });

			}
		}
	}

}
