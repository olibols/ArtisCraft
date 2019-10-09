#include "WorldTerrain.h"
#include "../Chunk/Region.h"
#include "StructureBuilder.h"

WorldTerrain::WorldTerrain(World& world) :
	_seed(world.getSeed()),
	_mainHeightmap(_seed),
	_mountainMap(_seed / 2)
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

			_currentRegion->setBlock(x, 65, z, BlockID::Water);
		}
	}

}

int WorldTerrain::getHeightAt(int x, int z)
{
	auto newX = (x + (_currentRegion->getLocation().x * CHUNK_SIZE));
	auto newZ = (z + (_currentRegion->getLocation().y * CHUNK_SIZE));

	int height = _mainHeightmap.GetHeight(newX, newZ);

	if (height > 65) {
		height *= _mountainMap.GetRidgedHeight(newX, newZ);
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
	auto newX = (x + (_currentRegion->getLocation().x * CHUNK_SIZE));
	auto newZ = (z + (_currentRegion->getLocation().y * CHUNK_SIZE));
	int height = _mainHeightmap.GetHeight(newX, newZ);

	if (height > 130) {
		return fillTopSoil(BlockID::Snow, BlockID::Dirt, BlockID::Stone);
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
	_mainHeightmap.GetNoise().SetFractalGain(0.5);
	_mainHeightmap.GetNoise().SetFractalGain(0.3);

	_mountainMap.SetAmplitude(2);
	_mountainMap.SetOffset(1);
	_mountainMap.GetNoise().SetFrequency(0.005);
	_mountainMap.GetNoise().SetFractalOctaves(6);
	_mountainMap.GetNoise().SetFractalGain(0.6);
}
