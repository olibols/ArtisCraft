#include "ChunkManager.h"

std::unordered_map<VectorXZ, Region> ChunkManager::_regions;

ChunkManager::ChunkManager(World & world) : _world(&world)
{
}

Region & ChunkManager::getRegion(int x, int z)
{

	if (_regions.find({ x, z }) == _regions.end())
	{
		VectorXZ    key{ x, z };
		Region       _region{ *_world, {x, z} };
		_regions.emplace(key, std::move(_region));
	}

	return _regions.at({ x, z });
}

void ChunkManager::makeMesh(int x, int z)
{
	getRegion(x, z).buildMesh();
}

void ChunkManager::update()
{
}

void ChunkManager::queueRegion(int x, int z)
{
}

std::unordered_map<VectorXZ, Region> ChunkManager::getRegions()
{
	return _regions;
}
