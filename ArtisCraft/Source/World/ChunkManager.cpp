#include "ChunkManager.h"

ChunkManager::ChunkManager(World & world) : _world(&world)
{
}

Region & ChunkManager::getRegion(int x, int z)
{
	VectorXZ    key{ x, z };

	if (!regionExistsAt(x, z))
	{
		Region       _region{ *_world, {x, z} };
		_regions.emplace(key, std::move(_region));
	}

	return _regions[key];
}

bool ChunkManager::makeMesh(int x, int z)
{
	for (int nx = -1; nx <= 1; nx++)
		for (int nz = -1; nz <= 1; nz++)
		{
			getRegion(x + nx, z + nz).load(_world->getWorldTerrain());
		}
	return getRegion(x, z).buildMesh();
}

bool ChunkManager::regionLoadedAt(int x, int z)
{
	if (!regionExistsAt(x, z)) return false;

	return _regions.at({ x, z }).hasLoaded();
}

bool ChunkManager::regionExistsAt(int x, int z)
{
	return _regions.find({ x, z }) != _regions.end();
}

void ChunkManager::loadRegion(int x, int z)
{
	getRegion(x, z).load(_world->getWorldTerrain());
}

RegionMap& ChunkManager::getRegions()
{
	return _regions;
}
