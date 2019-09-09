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
	StructureBuilder() = default;

	void build(Region& region);

	void addBlock(int x, int y, int z, BlockID block);

	void addColumn(int startX, int startY, int startZ, int height, BlockID block);
	void fill(int startX, int startZ, int y, int endX, int endZ, BlockID block);

private:

	std::vector<BuilderBlock> _blocks;
};