#include "WorldTerrain.h"
#include "../Chunk/Region.h"
#include "StructureBuilder.h"

WorldTerrain::WorldTerrain(World& world) : _dampnessMap(world.getSeed()),
										   _mainHeightmap(world.getSeed() / 2),
										   _treeMap(world.getSeed() / 3)
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

			int dampness = _dampnessMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);

			if (dampness > 80)
				if (_treeMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y) > 116)
					buildTree(x, height, z);

		}
	}

}

int WorldTerrain::getHeightAt(int x, int z)
{
	return _mainHeightmap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);
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
	int dampness = _dampnessMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);
	TopSoilBlocks topSoil;
	
	topSoil.TOP = BlockID::Grass;
	topSoil.MID = BlockID::Dirt;
	topSoil.BOTTOM = BlockID::Stone;

	if (dampness < 80) {
		topSoil.TOP = BlockID::Sand;
		topSoil.MID = BlockID::Sand;
	}

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
	NoiseParameters dampParams;
	dampParams.amplitude = 70;
	dampParams.offset = 1;
	dampParams.octaves = 6;
	dampParams.roughness = 0.53;
	dampParams.smoothness = 235;

	_dampnessMap.setNoiseParameters(dampParams);


	NoiseParameters mainParams;
	mainParams.amplitude = 70;
	mainParams.offset = 1;
	mainParams.octaves = 6;
	mainParams.roughness = 0.53;
	mainParams.smoothness = 235;

	_mainHeightmap.setNoiseParameters(mainParams);


	NoiseParameters treeParams;
	treeParams.amplitude = 70;
	treeParams.offset = 1;
	treeParams.octaves = 2;
	treeParams.roughness = 0.1;
	treeParams.smoothness = 1;

	_treeMap.setNoiseParameters(treeParams);
}
