#pragma once
#include "Block.h"
#include "../../Constants.h"
#include <array>

class ChunkSection {
public:
	ChunkSection();

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

private:
	bool outOfBounds(int value);
	int getIndex(int x, int y, int z);

	std::array<ChunkBlock, CHUNK_VOLUME> _blocks;
};