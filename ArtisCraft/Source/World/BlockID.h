#pragma once
#include <cstdint>

enum class BlockID : uint8_t {
	Air = 0,
	Grass,

	ERR_TYPE,
	MAX_TYPE
};