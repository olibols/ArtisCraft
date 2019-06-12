#pragma once
#include <GLM.h>
#include "../BlockID.h"

class BlockData;
class BlockType;

struct ChunkBlock {
public:
	ChunkBlock() = default;

	ChunkBlock(Block_t blockid);
	ChunkBlock(BlockID blockid);

	BlockData getData();
	BlockType getType();

	bool operator ==(ChunkBlock other) {
		return id == other.id;
	}

	Block_t id = 1;
};