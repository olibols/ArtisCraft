#include "ChunkBuildMesh.h"
#include "../BlockData.h"
#include "../Util/Utils.h"
#include "../BlockTypeDatabase.h"

std::vector<GLfloat> frontFace
	{
		0, 0, 1,
		1, 0, 1,
		1, 1, 1,
		0, 1, 1,
	};

std::vector<GLfloat> backFace
{
	1, 0, 0,
	0, 0, 0,
	0, 1, 0,
	1, 1, 0,
};

std::vector<GLfloat> leftFace
{
	0, 0, 0,
	0, 0, 1,
	0, 1, 1,
	0, 1, 0,
};

std::vector<GLfloat> rightFace
{
	1, 0, 1,
	1, 0, 0,
	1, 1, 0,
	1, 1, 1,
};

std::vector<GLfloat> topFace
{
	0, 1, 1,
	1, 1, 1,
	1, 1, 0,
	0, 1, 0,
};

std::vector<GLfloat> bottomFace
{
	0, 0, 0,
	1, 0, 0,
	1, 0, 1,
	0, 0, 1
};

ChunkBuildMesh::ChunkBuildMesh(Chunk& chunk) : _chunk(&chunk)
{
}

void ChunkBuildMesh::buildMesh(ChunkMesh chunkMesh)
{
	AdjacentPositions adjPositions;
	for (int8_t x = 0; x < CHUNK_SIZE; x++) { // Disgustingly embedded
		for (int8_t y = 0; y < CHUNK_SIZE; y++) {
			for (int8_t z = 0; x < CHUNK_SIZE; z++) {

				sf::Vector3i pos(x, y, z);
				ChunkBlock block = _chunk->getBlock(x, y, z);

				if (block == BlockID::Air) {
					continue;
				}

				_textureData = &block.getData().getTextureData();

				TextureData data = *_textureData;

				adjPositions.update(x, y, z);

				addMeshToFace(bottomFace, data.texBottomCoord, pos, adjPositions.down);
				addMeshToFace(topFace, data.texTopCoord, pos, adjPositions.up);

				addMeshToFace(leftFace, data.texSideCoord, pos, adjPositions.left);
				addMeshToFace(rightFace, data.texSideCoord, pos, adjPositions.right);

				addMeshToFace(frontFace, data.texSideCoord, pos, adjPositions.front);
				addMeshToFace(backFace, data.texSideCoord, pos, adjPositions.back);
			}
		}
	}
}

void ChunkBuildMesh::addMeshToFace(std::vector<GLfloat> face, sf::Vector2i textureCoords, sf::Vector3i blockPosition, sf::Vector3i blockFacing)
{
	if (shouldMakeFace(blockFacing, *_textureData)) {
		auto texCoords = BlockDatabase::get().atlas.getTexture(textureCoords);

		_mesh->addFace(face, texCoords, _chunk->getLocation(), blockPosition);
	}

}

bool ChunkBuildMesh::shouldMakeFace(sf::Vector3i adjBlock, TextureData texData)
{
	ChunkBlock block = _chunk->getBlock(adjBlock.x, adjBlock.y, adjBlock.z);

	if (block == BlockID::Air) {
		return true;
	}
	else {
		return false;
	}

}
