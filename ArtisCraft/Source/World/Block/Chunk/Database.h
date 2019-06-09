#pragma once
#include <array>

#include "../Types/BlockType.h"
#include "../BlockID.h"

class BlockDatabase {
public:
	static BlockDatabase& get();

	BlockType& getBlock(BlockID id);
	BlockData& getData(BlockID id);

private:
	BlockDatabase();

	std::array<std::unique_ptr<BlockType>, (std::size_t)BlockID::NUM_TYPES> _blocks;
};