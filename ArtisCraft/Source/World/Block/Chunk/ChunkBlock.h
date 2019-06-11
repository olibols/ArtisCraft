#pragma once
#include <GLM.h>
#include "../BlockID.h"

class ChunkBlock {
public:
	ChunkBlock() = default;
	ChunkBlock(BlockID block);

	~ChunkBlock();

	BlockID getBlock();
	void setBlock(BlockID& block);

private:
	BlockID _block;
};