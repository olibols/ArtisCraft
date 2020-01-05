#pragma once

#include "BlockID.h"

#include <glm.hpp>
#include <array>

class BlockTypeDatabase {
public:
	static BlockTypeDatabase& get();

	glm::vec3 getColor(BlockID id);

private:
	BlockTypeDatabase();
	
	std::array<glm::vec3, (int)BlockID::MAX_TYPE> m_blockColors;
};