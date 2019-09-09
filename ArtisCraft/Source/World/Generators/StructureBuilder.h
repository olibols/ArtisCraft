#pragma once
#include <vector>
#include "../Block/BlockID.h"

class Region;

struct BuilderBlock {
	BuilderBlock(BlockID block, int x, int y, int z) : block(block), x(x), y(y), z(z) {}

	BlockID block;
	int x, y, z;
};

class StructureBuilder {
public:
	StructureBuilder();

	void build(Region& region);

	void addColumn(int startX, int startY, int startZ, int height);

	void fillXZ(int startX, int y, int startZ, int endX, int endZ);

private:

	std::vector<BuilderBlock> _blocks;
	
};