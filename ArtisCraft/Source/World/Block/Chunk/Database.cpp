#include "Database.h"

#include "../Types/BlockType.h"

BlockDatabase & BlockDatabase::get()
{
	static BlockDatabase database;
	return database;
}

BlockType & BlockDatabase::getBlock(BlockID id)
{
	return *_blocks[(int)id];
}

BlockData & BlockDatabase::getData(BlockID id)
{
	return _blocks[(int)id]->getData();
}

BlockDatabase::BlockDatabase()
{
	_blocks[(int)BlockID::Air] = std::make_unique<DefaultBlock>("Air");
	_blocks[(int)BlockID::Dirt] = std::make_unique<DefaultBlock>("Dirt");
	_blocks[(int)BlockID::Stone] = std::make_unique<DefaultBlock>("Stone");
}
