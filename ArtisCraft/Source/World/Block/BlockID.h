#pragma once
#include <cstdint>

using Block_t = uint8_t;

enum class BlockID : Block_t {
	Dirt = 0,
	Stone,

	Air,

	NUM_TYPES
};