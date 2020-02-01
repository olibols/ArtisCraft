#include "StoneStructure.h"

void StoneStructure::build(StructureBuilder& builder, sf::Vector3i startPos)
{
	m_builder = &builder;
	auto& sp= startPos;

	m_builder->fill(sp.x - 3, sp.z - 3, sp.y - 3, sp.x + 3, sp.z + 3, sp.y + 9, BlockID::Stone);
	m_builder->fill(sp.x - 5, sp.z - 5, sp.y - 3, sp.x + 5, sp.z + 5, sp.y + 4, BlockID::Stone);
}
