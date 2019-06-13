#pragma once
#include <GLM.h>
#include "../BlockID.h"

struct ChunkBlock {
public:
	ChunkBlock();

	ChunkBlock(Block_t blockid);
	ChunkBlock(BlockID blockid);

	bool operator ==(ChunkBlock other) {
		return id == other.id;
	}

	Block_t id = 1;
};