#include "ChunkBlock.h"
#include "../BlockTypeDatabase.h"

ChunkBlock::ChunkBlock()
{
	id = (Block_t)BlockID::Air;
}

ChunkBlock::ChunkBlock(Block_t blockid)
{
	id = blockid;
}

ChunkBlock::ChunkBlock(BlockID blockid)
{
	id = (Block_t)blockid;
}
