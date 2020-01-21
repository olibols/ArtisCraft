#pragma once

#include "../WorldConstants.h"

#include <array>

using HeightMap = std::array<std::array<int, CHUNK_SIZE>, CHUNK_SIZE>;

class Column {
public:
	Column() = default;
	int getHeight(int x, int y);

	void setHeights(HeightMap& heightMap);

	inline void setLoaded() { m_isLoaded = true; };
	inline bool isLoaded() { return m_isLoaded; };
private:
	HeightMap m_heights;

	bool m_isLoaded = false;
};