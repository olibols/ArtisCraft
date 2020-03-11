#include "StoneStructure.h"

#include <array>

void StoneStructure::build(StructureBuilder& builder, sf::Vector3i startPos)
{
	m_builder = &builder;
	auto& sp= startPos;

	int x = sp.x;
	int y = sp.y;
	int z = sp.z;

	m_builder->addSphere(x + 2, y-4, z, 7, BlockID::Grass);
	m_builder->addSphere(x, y-2, z, 6, BlockID::Grass);
	m_builder->fill(x-3, z-3, y, x+3, z+3, y+13, BlockID::Stone);
	m_builder->addCube(x, z, y+6, 3, BlockID::Stone);
	m_builder->addCube(x+2, y+6, z-3, 2, BlockID::Stone);
}
