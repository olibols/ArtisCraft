#pragma once

#include "Chunk/Chunk.h"
#include "Coordinates.h"
#include "Terrain/WorldTerrain.h"

class ChunkManager {
public:
	ChunkManager(WorldTerrain& terrain);

	Chunk& addChunk(sf::Vector3i pos);
	void makeMesh(sf::Vector3i pos);
	void loadChunk(sf::Vector3i pos);

	Chunk& getChunk(sf::Vector3i pos);

	BlockID getBlock(sf::Vector3i pos);
	void setBlock(sf::Vector3i pos, BlockID block);

	bool hasChunk(sf::Vector3i pos);
	bool hasNeighbours(sf::Vector3i pos);

	void buildNeighbours(sf::Vector3i pos, WorldTerrain& terrain);

	ChunkPosMap<Chunk>& getChunks();

private:
	ChunkPosMap<Chunk> m_chunks;
	std::vector<Chunk*> m_chunkUpdates;

	WorldTerrain* m_terrain;

	int m_loadDistance = 2;
};