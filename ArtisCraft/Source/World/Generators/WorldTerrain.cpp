#include "WorldTerrain.h"

WorldTerrain::WorldTerrain(World& world) : _dampnessMap(world.getSeed())
{
	_world = &world;

	NoiseParameters dampParams;
	dampParams.amplitude = 100;
	dampParams.offset = 1;
	dampParams.octaves = 6;
	dampParams.roughness = 300;
	dampParams.smoothness = 60;

	_dampnessMap.setNoiseParameters(dampParams);

}
