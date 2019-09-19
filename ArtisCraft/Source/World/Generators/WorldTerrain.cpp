#include "WorldTerrain.h"
#include "../Chunk/Region.h"
#include "StructureBuilder.h"

WorldTerrain::WorldTerrain(World& world) :
	_mainHeightmap(world.getSeed() / 2),
	_mountainHeightmap(world.getSeed() * 2)
{
	_world = &world;
	_seed = _world->getSeed();

	setupGenerators();
}

void WorldTerrain::generateTerrainFor(Region& region)
{
	_currentRegion = &region;

	for (int x = 0; x < CHUNK_SIZE; x++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {

			TopSoilBlocks topSoil = getTopSoilAt(x, z);

			int height = getHeightAt(x, z);

			fillBlocksAt(x, height, z, topSoil);
		}
	}

}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);

	if (_mountainHeightmap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y) > 90) {
		height *= 3;
	}

	return height;
}

void WorldTerrain::fillBlocksAt(int x, int y, int z, TopSoilBlocks topSoil)
{
	for (int i = 0; i < y; i++) {
		if (i == y - 1) _currentRegion->setBlock(x, i, z, topSoil.TOP);
		else if (i > y - 5) _currentRegion->setBlock(x, i, z, topSoil.MID);
		else _currentRegion->setBlock(x, i, z, topSoil.BOTTOM);
	}
}

TopSoilBlocks WorldTerrain::getTopSoilAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);

	return fillTopSoil(BlockID::Grass, BlockID::Dirt, BlockID::Stone);
}

TopSoilBlocks WorldTerrain::fillTopSoil(BlockID top, BlockID middle, BlockID bottom)
{
	TopSoilBlocks topSoil;
	topSoil.TOP = top;
	topSoil.MID = middle;
	topSoil.BOTTOM = bottom;

	return topSoil;
}

void WorldTerrain::buildTree(int x, int y, int z)
{
	StructureBuilder treeBuilder;
	//(int y, int xStart, int xEnd, int zStart, int zEnd, BlockId block)

	treeBuilder.fill(x - 2, z - 2, y + 2, x + 2, z + 2, BlockID::Leaves);
	treeBuilder.fill(x - 2, z - 2, y + 3, x + 2, z + 2, BlockID::Leaves);
	treeBuilder.fill(x - 1, z - 1, y + 4, x + 1, z + 1, BlockID::Leaves);

	treeBuilder.addBlock(x, y + 5, z, BlockID::Leaves);
	treeBuilder.addBlock(x - 1, y + 5, z, BlockID::Leaves);
	treeBuilder.addBlock(x + 1, y + 5, z, BlockID::Leaves);
	treeBuilder.addBlock(x, y + 5, z + 1, BlockID::Leaves);
	treeBuilder.addBlock(x, y + 5, z - 1, BlockID::Leaves);

	treeBuilder.addColumn(x, y, z, 5, BlockID::Wood);
	
	treeBuilder.build(*_currentRegion);
}

void WorldTerrain::setupGenerators()
{
	NoiseParameters mainParams;
	mainParams.amplitude = 100;
	mainParams.offset = -50;
	mainParams.octaves = 6;
	mainParams.roughness = 0.35;
	mainParams.smoothness = 250;

	_mainHeightmap.setNoiseParameters(mainParams);


	NoiseParameters mountainParams;
	mountainParams.amplitude = 200;
	mountainParams.offset = -50;
	mountainParams.octaves = 6;
	mountainParams.roughness = 0.35;
	mountainParams.smoothness = 250;

	_mountainHeightmap.setNoiseParameters(mountainParams);
}
