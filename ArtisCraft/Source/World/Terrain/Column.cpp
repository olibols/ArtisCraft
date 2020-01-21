#include "Column.h"

int Column::getHeight(int x, int y)
{
	return m_heights[x][y];
}

void Column::setHeights(HeightMap& heightMap)
{
	m_heights = heightMap;
}
