#include "WorldTerrain.h"
#include "../Chunk/Region.h"
#include "StructureBuilder.h"

WorldTerrain::WorldTerrain(World& world) : 
_dampnessMap(world.getSeed()),
_mainHeightmap(world.getSeed() / 2),
_treeMap(world.getSeed() / 3),
_riverMap(world.getSeed() * 2),
_heatMap(world.getSeed() * 3)
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

			if (dampness > 80 && height > 64)
				if (_treeMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y) > 116)
					buildTree(x, height, z);

		}
	}

}

int WorldTerrain::getHeightAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);

	if (_riverMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y) < 60 && _riverMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y) > 50)
		height -= 3;

	return height;
}

void WorldTerrain::fillBlocksAt(int x, int y, int z, TopSoilBlocks topSoil)
{
	for (int i = 0; i < y; i++) {
		if (i == y - 1) _currentRegion->setBlock(x, i, z, topSoil.TOP);
		else if (i > y - 5) _currentRegion->setBlock(x, i, z, topSoil.MID);
		else _currentRegion->setBlock(x, i, z, topSoil.BOTTOM);

		_currentRegion->setBlock(x, 60, z, BlockID::Water);
	}
}

TopSoilBlocks WorldTerrain::getTopSoilAt(int x, int z)
{
	int height = _mainHeightmap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);
	int dampness = _dampnessMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);
	int heat = _heatMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);
	int rivermap = _riverMap.getHeight(x, z, _currentRegion->getLocation().x, _currentRegion->getLocation().y);

	if (height < 60) {
		return fillTopSoil(BlockID::Dirt, BlockID::Dirt, BlockID::Stone);
	}

	if (rivermap < 60 && rivermap > 55) {
		return fillTopSoil(BlockID::Water, BlockID::Water, BlockID::Water);
	}

	if ((heat < 80 && dampness > 15) || height > 100) {
		return fillTopSoil(BlockID::Snow, BlockID::Dirt, BlockID::Stone);
	}

	if (heat > 90 && dampness < 100) {
		fillTopSoil(BlockID::Sand, BlockID::Sand, BlockID::Stone);
	}

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
	NoiseParameters dampParams;
	dampParams.amplitude = 100;
	dampParams.offset = 50;
	dampParams.octaves = 3;
	dampParams.roughness = 0.53;
	dampParams.smoothness = 235;

	_dampnessMap.setNoiseParameters(dampParams);

	NoiseParameters hotParams;
	hotParams.amplitude = 100;
	hotParams.offset = 50;
	hotParams.octaves = 3;
	hotParams.roughness = 0.53;
	hotParams.smoothness = 235;

	_heatMap.setNoiseParameters(hotParams);

	NoiseParameters mainParams;
	mainParams.amplitude = 100;
	mainParams.offset = -50;
	mainParams.octaves = 6;
	mainParams.roughness = 0.53;
	mainParams.smoothness = 255;

	_mainHeightmap.setNoiseParameters(mainParams);


	NoiseParameters treeParams;
	treeParams.amplitude = 70;
	treeParams.offset = 1;
	treeParams.octaves = 2;
	treeParams.roughness = 0.1;
	treeParams.smoothness = 1;

	_treeMap.setNoiseParameters(treeParams);

	NoiseParameters riverParams;
	riverParams.amplitude = 100;
	riverParams.offset = -50;
	riverParams.octaves = 9;
	riverParams.roughness = 0.53;
	riverParams.smoothness = 205;

	_riverMap.setNoiseParameters(riverParams);
}
