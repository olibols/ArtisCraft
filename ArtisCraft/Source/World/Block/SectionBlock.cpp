#include "SectionBlock.h"

SectionBlock::SectionBlock()
{
	id = (Block_t)BlockID::Air;
}

SectionBlock::SectionBlock(Block_t blockid)
{
	id = blockid;
}

SectionBlock::SectionBlock(BlockID blockid)
{
	id = (Block_t)blockid;
}
