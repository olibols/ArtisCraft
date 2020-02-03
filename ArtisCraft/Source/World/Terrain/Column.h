#pragma once

#include "../WorldConstants.h"
#include "../BlockID.h"

#include <array>

using HeightMap = std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>;
using BlockMap = std::array<std::array<BlockID, CHUNK_SIZE>, CHUNK_SIZE>;

class Column {
public:
	Column() = default;
	int getHeight(int x, int y);
	BlockID getBlock(int x, int y);

	void setHeights(HeightMap& heightMap);
	void setBlocks(BlockMap& blockMap);

	inline void setHeightsLoaded() { m_isHeightsLoaded = true; };
	inline bool isHeightsLoaded() { return m_isHeightsLoaded; };

	inline void setBlocksLoaded() { m_isBlocksLoaded = true; };
	inline bool isBlocksLoaded() { return m_isBlocksLoaded; };
private:
	HeightMap m_heights;
	BlockMap m_blocks;

	bool m_isHeightsLoaded = false;
	bool m_isBlocksLoaded = false;
};