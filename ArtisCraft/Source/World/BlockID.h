#pragma once
#include <cstdint>

enum class BlockID : unsigned char {
	Air = 0,
	Grass,
	Darkgrass,
	Sand,
	Wood,
	Leaf,
	Darkleaf,
	Stone,
	Water,
	Red,

	ERR_TYPE,
	FULL_CHUNKTYPE,
	MAX_TYPE
};