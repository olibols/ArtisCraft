#include "WorldTerrain.h"
#include "../Chunk/Region.h"

WorldTerrain::WorldTerrain(World& world) : _dampnessMap(world.getSeed()),
										   _mainHeightmap(world.getSeed())
{
	_world = &world;
	_seed = _world->getSeed();
}

void WorldTerrain::generateTerrainFor(Region & region)
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
		topSoil.TOP = BlockID::Stone;
	}

	return topSoil;
}

void WorldTerrain::setupGenerators()
{
	NoiseParameters dampParams;
	dampParams.amplitude = 100;
	dampParams.offset = 1;
	dampParams.octaves = 6;
	dampParams.roughness = 300;
	dampParams.smoothness = 60;

	_dampnessMap.setNoiseParameters(dampParams);
}
