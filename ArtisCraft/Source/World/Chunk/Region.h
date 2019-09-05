#pragma once
#include "Chunk.h"
#include "../Generators/NoiseGenerator.h"


class World;
class RenderMaster;

class Region {
public:
	Region(World& world, sf::Vector2i location);

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	void draw(RenderMaster& renderer);

	inline bool hasLoaded() { return isLoaded; };
	void load();

	inline sf::Vector2i getLocation() { return _location; };

	bool buildMesh();

	Chunk& getChunk(int chunkIndex);

private:

	NoiseGenerator* temp_noiseGen = new NoiseGenerator(420);

	void addChunk();
	void addChunkBlockTarget(int blockY);
	void addChunkIndexTarget(int index);

	bool outOfBounds(int x, int y, int z);
	
	bool isLoaded = false;

	std::vector<Chunk> _chunks;
	sf::Vector2i _location;


	World* _world;
};