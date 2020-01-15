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

BlockTypeDatabase::BlockTypeDatabase()
{
	m_blockColors[(int)BlockID::Air] = glm::vec3(1.0);
	m_blockColors[(int)BlockID::Grass] = glm::vec3(124 / 255.0, 252 / 255.0, 0 / 255.0);
}
