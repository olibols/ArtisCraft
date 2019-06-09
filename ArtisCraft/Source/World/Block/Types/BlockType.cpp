#include "BlockType.h"

BlockType::BlockType(std::string fileName) : _data(fileName)
{
}

BlockData & BlockType::getData()
{
	return _data;
}
