#include "BlockType.h"

BlockType::BlockType(std::string fileName) : _data(fileName)
{
}

const BlockData BlockType::getData()
{
	return _data;
}
