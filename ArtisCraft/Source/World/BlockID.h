#pragma once
#include <cstdint>

enum class BlockID : unsigned char {
	Air = 0,
	Grass,
	Sand,
	Wood,
	Leaf,
	Stone,
	Water,

	ERR_TYPE,
	FULL_CHUNKTYPE,
	MAX_TYPE
};