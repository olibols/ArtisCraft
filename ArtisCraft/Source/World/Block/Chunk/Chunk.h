#pragma once
#include "ChunkBlock.h"
#include "../../Constants.h"
#include "ChunkMesh.h"

#include <array>

class Chunk {
public:
	Chunk();
	

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	ChunkMesh _mesh;

private:

	bool outOfBounds(int x, int y, int z);

	int getIndex(int x, int y, int z);

	std::array<ChunkBlock, CHUNK_VOLUME> _blocks;

	glm::vec3 _location;
};