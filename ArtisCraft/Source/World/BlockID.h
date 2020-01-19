#pragma once
#include <cstdint>

enum class BlockID : uint8_t {
	Air = 0,
	Grass,
	Sand,

	ERR_TYPE,
	FULL_CHUNKTYPE,
	MAX_TYPE
};