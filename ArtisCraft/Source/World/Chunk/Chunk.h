#pragma once

#include "../BlockID.h"
#include "ChunkBlock.h"
#include "../WorldConstants.h"
#include "ChunkMesh.h"
#include "../../Renderer/MasterRenderer.h"

#include <SFML/Graphics.hpp>
#include <array>

class ChunkManager;

class Layer {
public:
	inline void update(ChunkBlock block) {
		if (block == BlockID::Air) m_solidBlockCount--;
		else m_solidBlockCount++;
	}

	inline bool isSolid() { return m_solidBlockCount == CHUNK_AREA; };
private:
	int m_solidBlockCount = 0;
};

class Chunk {
public:
	Chunk(sf::Vector3i pos, ChunkManager& cm);

	void setBlock(int x, int y, int z, BlockID block);
	BlockID getBlock(int x, int y, int z);

	Chunk& getAdjChunk(int x, int y, int z);

	sf::Vector3i getLocation();

	void buildMesh();
	void bufferMesh();
	ChunkMesh& getMesh();
	bool hasMesh();

	Layer getLayer(int y);

	bool isLoaded();
	void setLoaded();
	bool isSeeded();
	void setSeeded();

	bool hasBlocks();

	void draw(MasterRenderer& renderer);

private:
	std::array<ChunkBlock, CHUNK_VOLUME> m_blocks;
	std::array<Layer, CHUNK_SIZE> m_layers;

	int getIndex(int x, int y, int z);
	bool isOutOfBounds(int index);

	ChunkMesh m_mesh;
	bool m_hasMesh = false;
	bool m_isBuffered = false;
	bool m_hasBlocks = false;

	bool m_isLoaded = false;
	bool m_isSeeded = false;

	sf::Vector3i m_location;
	ChunkManager* m_chunkManager;
};