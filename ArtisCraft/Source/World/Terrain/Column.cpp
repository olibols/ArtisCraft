#include "Column.h"

int Column::getHeight(int x, int y)
{
	return m_heights[x][y];
}

BlockID Column::getBlock(int x, int y)
{
	return m_blocks[x][y];
}

void Column::setHeights(HeightMap& heightMap)
{
	m_heights = heightMap;
}

void Column::setBlocks(BlockMap& blockMap)
{
	m_blocks = blockMap;
}
