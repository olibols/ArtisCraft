#pragma once
#include "Chunk/Region.h"

#include <Utils.h>

#include <unordered_map>

class World;

class ChunkManager {
public:
	ChunkManager(World& world);

	Region& getRegion(int x, int z);
	std::unordered_map<VectorXZ, Region> getRegions();

	bool makeMesh(int x, int z);

	bool regionLoadedAt(int x, int z);
	bool regionExistsAt(int x, int z);

	void loadRegion(int x, int z);

private:
	static std::unordered_map<VectorXZ, Region> _regions;

	World* _world;
};