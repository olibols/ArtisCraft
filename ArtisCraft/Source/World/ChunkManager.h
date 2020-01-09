#pragma once

#include "Chunk/Chunk.h"
#include "Coordinates.h"
#include "Terrain/WorldTerrain.h"

class ChunkManager {
public:
	Chunk& addChunk(sf::Vector3i pos);

	Chunk& getChunk(sf::Vector3i pos);

	BlockID getBlock(sf::Vector3i pos);
	void setBlock(sf::Vector3i pos, BlockID block);

	bool hasChunk(sf::Vector3i pos);
	bool hasNeighbours(sf::Vector3i pos);

	void buildNeighbours(sf::Vector3i pos, WorldTerrain& terrain);

	ChunkPosMap<Chunk>& getChunks();

private:
	ChunkPosMap<Chunk> m_chunks;
};