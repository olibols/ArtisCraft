#pragma once

#include "../World.h"
#include "NoiseGenerator.h"

class WorldTerrain
{
public:
	WorldTerrain(World& world);

private:

	World* _world;
	
	NoiseGenerator _dampnessMap;

};