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


	void updateLoadList(Camera& cam);
	void updateSetupList(Camera& cam, WorldTerrain& terrain);
	void updateRenderList(Camera& cam);

	std::vector<Chunk*>& getLoadlist();
	std::vector<Chunk*>& getSetuplist();
	std::vector<Chunk*>& getRenderlist();

	ChunkPosMap<Chunk>& getChunks();

private:
	ChunkPosMap<Chunk> m_chunks;

	std::vector<Chunk*> m_loadList;
	std::vector<Chunk*> m_setupList;
	std::vector<Chunk*> m_renderlist;

	int m_loadDistance = 2;
};