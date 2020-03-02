#pragma once

#include "Chunk/Chunk.h"
#include "Coordinates.h"
#include "Terrain/Column.h"

class WorldTerrain;

class ChunkManager {
public:
	ChunkManager(WorldTerrain& terrain);

	Chunk& addChunk(sf::Vector3i pos);
	Column& addColumn(sf::Vector2i pos);
	void makeMesh(sf::Vector3i pos);

	void loadChunk(sf::Vector3i pos);

	Chunk& getChunk(sf::Vector3i pos);

	BlockID getBlock(sf::Vector3i pos);
	void setBlock(sf::Vector3i pos, BlockID block);

	bool hasChunk(sf::Vector3i pos);
	bool hasNeighbours(sf::Vector3i pos);

	void buildNeighbours(sf::Vector3i pos, WorldTerrain& terrain);

	ChunkPosMap<Chunk>& getChunks();

	inline ChunkHeightMap<Column>& getHeights() { return m_heightMap; };

private:
	ChunkPosMap<Chunk> m_chunks;
	ChunkHeightMap<Column> m_heightMap;

	WorldTerrain* m_terrain;

	int m_loadDistance = 2;
};