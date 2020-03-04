#include "OakTreeStructure.h"

void OakTreeStructure::build(StructureBuilder & builder, sf::Vector3i startPos)
{
	m_builder = &builder;
	auto& sp = startPos;

	int x = sp.x;
	int y = sp.y;
	int z = sp.z;

	builder.addColumn(x, y, z, 8, BlockID::Wood);
	
}
