#pragma once
#include "ChunkBlock.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include "ChunkMesh.h"
#include <array>

class World;

class Chunk {
public:
	Chunk(sf::Vector3i position, World& world);
	
	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	sf::Vector3i getLocation();


	void deleteMesh();
	ChunkMesh mesh;

private:

	sf::Vector3i toWorldPos(int x, int y, int z);

	bool outOfBounds(int value);

	int getIndex(int x, int y, int z);

	std::array<ChunkBlock, CHUNK_VOLUME> _blocks;

	sf::Vector3i _location;

	World* _world;
};