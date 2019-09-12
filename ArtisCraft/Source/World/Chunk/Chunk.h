#pragma once
#include "ChunkBlock.h"
#include "../Constants.h"
#include <SFML/Graphics.hpp>
#include "ChunkMesh.h"
#include <array>
#include <queue>

class World;
class Chunk;

struct LightNode
{
	LightNode(short index, Chunk* chunk) : index(index), chunk(chunk) {};
	short index;
	Chunk* chunk;
};

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

	bool hasFaces();

	inline bool hasMesh() { return _hasMesh; };
	inline bool hasBuffered() { return _hasMeshBuffered; };
	inline bool hasBlocks() { return _hasBlocks; };

	void buildMesh();
	void bufferMesh();

	ChunkLayer& getLayer(int y);
	Chunk& getAdjacentChunk(int x, int z);

	inline ChunkMesh& getMesh() { return _mesh; };

	inline int getSunlight(int x, int y, int z) {
		return (_lightMap[x][y][z] >> 4) & 0xF;
	}

	inline void setSunlight(int x, int y, int z, int lightlevel) {
		_lightMap[x][y][z] = (_lightMap[x][y][z] & 0xF) | (lightlevel << 4);
	}

	inline int getBlocklight(int x, int y, int z) {
		return _lightMap[x][y][z] & 0xF;
	}

	inline void setBlockLight(int x, int y, int z, int lightLevel) {
		_lightMap[x][y][z] = (_lightMap[x][y][z] & 0xF0) | lightLevel;
	}
	   
	inline std::queue<LightNode>& getNodeQueue() { return _lightNodeQueue; };

	void fillLight();

private:

	unsigned char _lightMap[CHUNK_SIZE][CHUNK_SIZE][CHUNK_SIZE];
	std::queue<LightNode> _lightNodeQueue;
	void processNode(int x, int nx, int y, int ny, int z, int nz, int lightLevel, Chunk* chunk);

	sf::Vector3i toWorldPos(int x, int y, int z);
	bool outOfBounds(int value);
	int getIndex(int x, int y, int z);

	bool _hasMeshBuffered = false;
	bool _hasMesh = false;
	bool _hasBlocks = false;

	ChunkMesh _mesh;

	std::array<ChunkLayer, CHUNK_SIZE> _layers;
	std::array<ChunkBlock, CHUNK_VOLUME> _blocks;
	sf::Vector3i _location;
	World* _world;
};