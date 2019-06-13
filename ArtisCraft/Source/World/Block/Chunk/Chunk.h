#pragma once
#include "ChunkBlock.h"
#include "../../Constants.h"
#include <SFML/Graphics.hpp>
#include "ChunkMesh.h"
#include <array>

class Chunk {
public:
	Chunk();
	

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	sf::Vector3i getLocation();

	ChunkMesh mesh;

private:

	bool outOfBounds(int x, int y, int z);

	int getIndex(int x, int y, int z);

	std::array<ChunkBlock, CHUNK_VOLUME> _blocks;

	sf::Vector3i _location;
};