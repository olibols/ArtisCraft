#include "StoneStructure.h"

#include <array>

void StoneStructure::build(StructureBuilder& builder, sf::Vector3i startPos)
{
	m_builder = &builder;
	auto& sp= startPos;

	m_builder->fill(-2, -2, -3, 2, 2, 15, BlockID::Stone);
	m_builder->addBlock(0, 16, 0, BlockID::Stone);
}
