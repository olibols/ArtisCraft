#pragma once
#include <cstdint>

using Block_t = uint8_t;

enum class BlockID : Block_t {
	Air = 0,

	Dirt,
	Grass,
	Stone,
	Wood,
	Bedrock,
	Water,
	Sand,
	Leaves,
	Snow,

	NUM_TYPES
};
