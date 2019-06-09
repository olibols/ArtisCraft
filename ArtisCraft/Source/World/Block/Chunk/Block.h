#pragma once
#include "../BlockID.h"

class BlockData;
class BlockType;

struct ChunkBlock {
	ChunkBlock() = default;

	ChunkBlock(Block_t id);
	ChunkBlock(BlockID id);

	Block_t ID = 1;

	BlockData& getBlockData();
	BlockType& getType();
};