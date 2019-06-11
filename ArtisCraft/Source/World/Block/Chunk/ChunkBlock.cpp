#include "ChunkBlock.h"

ChunkBlock::ChunkBlock(BlockID block)
{
	_block = block;
}

ChunkBlock::~ChunkBlock()
{

}

BlockID ChunkBlock::getBlock()
{
	return _block;
}

void ChunkBlock::setBlock(BlockID& block)
{
	_block = block;
}
