#pragma once

#include "../World.h"
#include "NoiseGenerator.h"


struct TopSoilBlocks {
	BlockID TOP;
	BlockID MID;
	BlockID BOTTOM;
};

class Region;

class WorldTerrain
{
public:
	WorldTerrain(World& world);

	void generateTerrainFor(Region& region);

private:

	int getHeightAt(int x, int z);
	void fillBlocksAt(int x, int y, int z, TopSoilBlocks topSoil);
	TopSoilBlocks getTopSoilAt(int x, int z);

	TopSoilBlocks fillTopSoil(BlockID top, BlockID middle, BlockID bottom);

	void buildTree(int x, int y, int z);

	void setupGenerators();

	int _seed;
	World* _world;
	Region* _currentRegion;

	NoiseGenerator _mainHeightmap;
	NoiseGenerator _mountainHeightmap;
};