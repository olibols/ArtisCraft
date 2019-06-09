#include "Block.h"
#include "Database.h"

ChunkBlock::ChunkBlock(Block_t id) : ID(id)
{
}

ChunkBlock::ChunkBlock(BlockID id) : ID((Block_t)id)
{

}

BlockData & ChunkBlock::getBlockData()
{
	return BlockDatabase::get().getData((BlockID)ID);
}

BlockType & ChunkBlock::getType()
{
	return BlockDatabase::get().getBlock((BlockID)ID);
}
