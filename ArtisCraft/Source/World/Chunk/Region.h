#pragma once
#include "Chunk.h"


class World;
class RenderMaster;

class Region {
public:
	Region(World& world, sf::Vector2i location);

	void setBlock(int x, int y, int z, ChunkBlock block);
	ChunkBlock getBlock(int x, int y, int z);

	void draw(RenderMaster& renderer);

	void buildMesh(int y);
	void buildMesh();

private:

	bool outOfBounds(int x, int y, int z);
	

	std::vector<Chunk> _chunks;
	sf::Vector2i _location;


	World* _world;
};