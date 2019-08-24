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

BlockData BlockDatabase::getData(BlockID id)
{
	return _blocks[(int)id]->getData();
}

BlockDatabase::BlockDatabase() : atlas("ArtisPack")
{
	_blocks[(int)BlockID::Air] = std::make_unique<DefaultBlock>("air");
	_blocks[(int)BlockID::Dirt] = std::make_unique<DefaultBlock>("dirt");
	_blocks[(int)BlockID::Grass	] = std::make_unique<DefaultBlock>("grass");
	_blocks[(int)BlockID::Stone] = std::make_unique<DefaultBlock>("stone");
	_blocks[(int)BlockID::Wood] = std::make_unique<DefaultBlock>("wood");
	_blocks[(int)BlockID::Bedrock] = std::make_unique<DefaultBlock>("bedrock");
}
