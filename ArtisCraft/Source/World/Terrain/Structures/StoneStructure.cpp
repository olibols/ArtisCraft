#include "StoneStructure.h"

#include <array>

void StoneStructure::build(StructureBuilder& builder, sf::Vector3i startPos)
{
	m_builder = &builder;
	auto& sp= startPos;

	int x = sp.x;
	int y = sp.y;
	int z = sp.z;

	m_builder->fill(x-3, z-3, y-3, x+3, z+3, y+10, BlockID::Stone);
	m_builder->addCube(x, z, y+3, 3, BlockID::Stone);
	m_builder->addCube(x+2, y+3, z-3, 2, BlockID::Stone);
}
