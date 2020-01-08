#pragma once

#include "../BlockID.h"
#include "../Terrain/WorldTerrain.h"

class Chunk;

namespace ChunkTools {
	void fillChunk(Chunk& chunk, BlockID block);

	void fillChunk(Chunk& chunk, WorldTerrain& terrain);
}