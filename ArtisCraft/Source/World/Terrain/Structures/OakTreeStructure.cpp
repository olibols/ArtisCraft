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


	builder.addColumn(sx, sy - 10, sz, 6, BlockID::Wood);
	builder.addSphere(sx, sy - 13, sz, 4, BlockID::Grass);

	srand(time(NULL));
	if (rand() % 100 > 50) { // is normal tree
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
	else {
		for (int x = sx - 5; x < sx + 5; x++)
			for (int y = sy - 5; y < sy + 5; y++)
				for (int z = sz - 5; z < sz + 5; z++) {
					if (glm::length(glm::vec3(sx, sy, sz) - glm::vec3(x, y, z)) < 5) {
						if (noise.GetHeight1_0(x, y, z) < 0.05) {
							srand(time(NULL) * x*y*z);
							if (rand() % 100 < 5) {
								builder.addBlock(x, y, z, BlockID::Red);
							}
							else {
								builder.addBlock(x, y, z, BlockID::Leaf);
							}
						}
					}
				}

		builder.addBlock(sx + 2, sp.y + 1, sz, BlockID::Red);
		builder.addBlock(sx - 1, sp.y, sz + 2, BlockID::Red);
		builder.addBlock(sx + 2, sp.y, sz - 2, BlockID::Red);
	}
}

