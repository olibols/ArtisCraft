#pragma once

#include "../Chunk/Region.h"
#include "../World.h"
#include "NoiseGenerator.h"


struct TopSoilBlocks {
	BlockID TOP;
	BlockID MID;
	BlockID BOTTOM;
};


class WorldTerrain
{
public:
	WorldTerrain(World& world);

	void generateTerrainFor(Region& region);

private:

	int getHeightAt(int x, int z);
	void fillBlocksAt(int x, int y, int z, TopSoilBlocks topSoil);
	TopSoilBlocks getTopSoilAt(int x, int z);

	void setupGenerators();

	int _seed;
	World* _world;
	Region* _currentRegion;

	NoiseGenerator _dampnessMap;

	NoiseGenerator _mainHeightmap;
};