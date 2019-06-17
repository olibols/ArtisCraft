#pragma once
#include "Chunk/ChunkBlock.h"
#include "../Renderer/RenderMaster.h"
#include "Chunk/Region.h"

class World {
public:
	World();

	ChunkBlock getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, ChunkBlock block);

	void render(RenderMaster& renderer);

private:
	
	Region _region;
};