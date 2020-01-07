#pragma once

#include "../BlockID.h"
#include "../WorldConstants.h"
#include "ChunkMesh.h"
#include "../../Renderer/MasterRenderer.h"

#include <SFML/Graphics.hpp>
#include <array>

class Chunk {
public:
	Chunk(sf::Vector3i pos);

	void setBlock(int x, int y, int z, BlockID block);
	BlockID getBlock(int x, int y, int z);

	sf::Vector3i getLocation();

	void buildMesh();
	void bufferMesh();
	ChunkMesh& getMesh();
	bool hasMesh();

	void draw(MasterRenderer& renderer);

private:
	std::array<BlockID, CHUNK_VOLUME> m_blocks;
	int getIndex(int x, int y, int z);
	bool isOutOfBounds(int index);

	ChunkMesh m_mesh;
	bool m_hasMesh = false;
	bool m_isBuffered = false;

	sf::Vector3i m_location;

};