#pragma once
#include "ChunkBlock.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include "ChunkMesh.h"
#include "../AABB/AABB.h"
#include <array>
#include <atomic>
#include <memory>

class World;

class ChunkLayer {
public:
	inline void update(ChunkBlock block) {
		if (block == BlockID::Air) _solidBlockCount--;
		else _solidBlockCount++;
	}

	inline bool isAllSolid() { return _solidBlockCount == CHUNK_AREA; }

private:
	int _solidBlockCount = 0;
};

class Chunk {
public:
	Chunk(sf::Vector3i position, World& world);
	
	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	sf::Vector3i getLocation();

	void buildMesh();

	ChunkLayer& getLayer(int y);
	Chunk& getAdjacentChunk(int x, int z);

	inline ChunkMesh& getMesh() { return _mesh; };

	inline bool hasMesh() { return _hasMesh; };
	inline bool hasBufferedMesh() { return _hasMeshBuffered; };

	ChunkMesh _mesh;

	void bufferMesh();
	
	inline AABB getBoundingBox() { return _aabb; };
	   
private:

	sf::Vector3i toWorldPos(int x, int y, int z);
	bool outOfBounds(int value);
	int getIndex(int x, int y, int z);

	bool _hasMesh = false;
	bool _hasMeshBuffered = false;

	AABB _aabb;

	std::array<ChunkLayer, CHUNK_SIZE> _layers;
	std::array<ChunkBlock, CHUNK_VOLUME> _blocks;
	sf::Vector3i _location;
	World* _world;
};