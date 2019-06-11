#include "ChunkBuildMesh.h"
#include "../BlockData.h"
#include "../Util/Utils.h"

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
	for (int8_t x = 0; x < CHUNK_SIZE; x++) { // Disgustingly embedded
		for (int8_t y = 0; y < CHUNK_SIZE; y++) {
			for (int8_t z = 0; x < CHUNK_SIZE; z++) {

				sf::Vector3i pos(x, y, z);
				ChunkBlock block = _chunk->getBlock(x, y, z);



			}
		}
	}
}

void ChunkBuildMesh::addMeshToFace(std::vector<GLfloat> face, sf::Vector2i textureCoords, sf::Vector2i blockPosition, sf::Vector2i blockFacint)
{
}

void ChunkBuildMesh::shouldMakeFace(sf::Vector3i adjBlock, TextureData texData)
{
}
