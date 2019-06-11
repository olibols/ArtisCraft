#pragma once
#include "../BlockData.h"

class BlockType {
public:
	BlockType(std::string fileName);

	const BlockData getData();
private:

	BlockData _data;
};

class DefaultBlock : public BlockType {
public:
	DefaultBlock(std::string fileName) : BlockType(fileName) {}
};