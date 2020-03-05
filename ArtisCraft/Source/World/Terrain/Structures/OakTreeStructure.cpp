#include "OakTreeStructure.h"

#include "../Generators/NoiseWrapper3D.h"

void OakTreeStructure::build(StructureBuilder & builder, sf::Vector3i startPos)
{
	m_builder = &builder;
	auto& sp = startPos;

	NoiseWrapper3D noise(time(NULL));

	int sx = sp.x;
	int sy = sp.y + 10;
	int sz = sp.z;

	/*for(int nx = x; nx < x + 10; nx++)
	for(int ny = y; ny < y + 10; ny++)
		for (int nz = z; nz < z + 10; nz++) {
			
	}*/

	builder.addColumn(sx, sy - 10, sz, 6, BlockID::Wood);

	for (int x = sx - 5; x < sx + 5; x++)
		for (int y = sy - 5; y < sy + 5; y++)
			for (int z = sz - 5; z < sz + 5; z++) {
				if (glm::length(glm::vec3(sx, sy, sz) - glm::vec3(x, y, z)) < 5) {
					if (noise.GetHeight1_0(x, y, z) < 0.05) {
						builder.addBlock(x, y, z, BlockID::Leaf);
					}
				}
			}
}
