#include "BlockTypeDatabase.h"

BlockDatabase & BlockDatabase::get()
{
	static BlockDatabase db;
	return db;
}

BlockType BlockDatabase::getBlock(BlockID id)
{
	return *_blocks[(int)id];
}

BlockData BlockDatabase::getdata(BlockID id)
{
	return _blocks[(int)id]->getData();
}

BlockDatabase::BlockDatabase() : atlas("ArtisPack")
{
	_blocks[(int)BlockID::Air] = std::make_unique<DefaultBlock>("Air");
	_blocks[(int)BlockID::Dirt] = std::make_unique<DefaultBlock>("Dirt");
	_blocks[(int)BlockID::Stone] = std::make_unique<DefaultBlock>("Stone");
}
