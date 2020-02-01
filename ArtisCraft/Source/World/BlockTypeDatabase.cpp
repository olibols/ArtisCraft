#include "BlockTypeDatabase.h"

BlockTypeDatabase & BlockTypeDatabase::get()
{
	static BlockTypeDatabase db;
	return db;
}

glm::vec3 BlockTypeDatabase::getColor(BlockID id)
{
	return m_blockColors[(int)id];
}

glm::vec3 normaliseColour(int r, int g, int b) {
	return { r / 250.0, g / 250.0, b / 250.0 };
}

BlockTypeDatabase::BlockTypeDatabase()
{
	m_blockColors[(int)BlockID::Air] = glm::vec3(1.0);
	m_blockColors[(int)BlockID::Grass] = normaliseColour(167, 205, 44);
	m_blockColors[(int)BlockID::Sand] = normaliseColour(251, 238, 194);
	m_blockColors[(int)BlockID::Wood] = normaliseColour(86, 67, 52);
	m_blockColors[(int)BlockID::Leaf] = normaliseColour(82, 107, 45);
}
