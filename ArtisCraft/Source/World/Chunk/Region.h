#pragma once
#include "Chunk.h"


class World;
class RenderMaster;

class Region {
public:
	Region(World& world);

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	void draw(RenderMaster& renderer);

private:

	bool outOfBounds(int x, int y, int z);

	std::vector<Chunk> _chunks;

	World* _world;
};