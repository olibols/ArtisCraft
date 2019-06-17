#include "ChunkMeshBuilder.h"
#include <Utils.h>
#include "../Block/BlockTypeDatabase.h"

const std::vector<GLfloat> frontFace
{
	0, 0, 1,
	1, 0, 1,
	1, 1, 1,
	0, 1, 1,
};

const std::vector<GLfloat> backFace
{
	1, 0, 0,
	0, 0, 0,
	0, 1, 0,
	1, 1, 0,
};

const std::vector<GLfloat> leftFace
{
	0, 0, 0,
	0, 0, 1,
	0, 1, 1,
	0, 1, 0,
};

const std::vector<GLfloat> rightFace
{
	1, 0, 1,
	1, 0, 0,
	1, 1, 0,
	1, 1, 1,
};

const std::vector<GLfloat> topFace
{
	0, 1, 1,
	1, 1, 1,
	1, 1, 0,
	0, 1, 0,
};

const std::vector<GLfloat> bottomFace
{
	0, 0, 0,
	1, 0, 0,
	1, 0, 1,
	0, 0, 1
};

int faceCount = 0;

ChunkMeshBuilder::ChunkMeshBuilder(Chunk & chunk)
{
	_chunk = &chunk;
	_texData = new TextureData;
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
				
				if (block == BlockID::Air) {
					continue;
				}

				_texData = &BlockDatabase::get().getData((BlockID)block.id).getTextureData();

				directions.update(x, y, z);

				addFace(bottomFace, _texData->texBottomCoord, position, directions.down);
				addFace(topFace, _texData->texTopCoord, position, directions.up);

				addFace(leftFace, _texData->texSideCoord, position, directions.left);
				addFace(rightFace, _texData->texSideCoord, position, directions.right);

				addFace(frontFace, _texData->texSideCoord, position, directions.front);
				addFace(backFace, _texData->texSideCoord, position, directions.back);
			}
		}
	}

	printf("Built chunk mesh, face count: %i \n", faceCount);

}

bool ChunkMeshBuilder::shouldMakeFace(sf::Vector3i blockPosition, TextureData texData)
{
	ChunkBlock block = _chunk->getBlock(blockPosition.x, blockPosition.y, blockPosition.z);

	if (block == BlockID::Air) {
		return true;
	}
	else {
		return false;
	}
}

void ChunkMeshBuilder::addFace(std::vector<GLfloat> blockFace, sf::Vector2i texCoords, sf::Vector3i blockPosition, sf::Vector3i blockFacing)
{
	if (shouldMakeFace(blockFacing, *_texData)) {
		faceCount++;
		auto textureCoords = BlockDatabase::get().atlas.getTexture(texCoords);

		_mesh->addFace(blockFace, textureCoords, _chunk->getLocation(), blockPosition);
	}
}
