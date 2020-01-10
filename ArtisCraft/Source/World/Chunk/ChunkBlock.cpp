#include "ChunkBlock.h"

ChunkBlock::ChunkBlock()
{
	id = BlockID::Air;
}

ChunkBlock::ChunkBlock(BlockID block)
{
	id = block;
}
