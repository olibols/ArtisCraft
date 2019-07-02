#pragma once
#include "Chunk/Region.h"

#include <Utils.h>

#include <unordered_map>

class World;

class ChunkManager {
public:
	ChunkManager(World& world);

	Region& getRegion(int x, int z);

	void makeMesh(int x, int z);

	void update();

	void queueRegion(int x, int z);

	std::unordered_map<VectorXZ, Region> getRegions();

private:
	static std::unordered_map<VectorXZ, Region> _regions;

	World* _world;

};