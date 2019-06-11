#pragma once
#include "BlockID.h"
#include "../../Renderer/Texture/TextureAtlas.h"
#include "Types/BlockType.h"
#include "BlockData.h"

#include <array>

class BlockDatabase {
public:
	static BlockDatabase& get();

	BlockType getBlock(BlockID id);
	BlockData getdata(BlockID id);

private:
	BlockDatabase();

	TextureAtlas _atlas;
	
	std::array<std::unique_ptr<BlockType>, (size_t)BlockID::NUM_TYPES> _blocks;

};