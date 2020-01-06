#include "Coordinates.h"

#include "WorldConstants.h"

sf::Vector3i worldToChunkPos(sf::Vector3i pos)
{
	return toChunkPos(pos);
}

sf::Vector3i toChunkPos(sf::Vector3i pos)
{
	int x = pos.x;
	int y = pos.y;
	int z = pos.z;
	return {
	x < 0 ? ((x - CHUNK_SIZE) / CHUNK_SIZE) : (x / CHUNK_SIZE),
	y < 0 ? ((y - CHUNK_SIZE) / CHUNK_SIZE) : (y / CHUNK_SIZE),
	z < 0 ? ((z - CHUNK_SIZE) / CHUNK_SIZE) : (z / CHUNK_SIZE),
	};
}

sf::Vector3i toLocalBlockPos(sf::Vector3i pos)
{
	return { (CHUNK_SIZE + (pos.x % CHUNK_SIZE)) % CHUNK_SIZE,
			(CHUNK_SIZE + (pos.y % CHUNK_SIZE)) % CHUNK_SIZE,
			(CHUNK_SIZE + (pos.z % CHUNK_SIZE)) % CHUNK_SIZE };
}

sf::Vector3i toGlobalBlockPos(sf::Vector3i blockPos, sf::Vector3i chunkPos)
{
	return {
	chunkPos.x * CHUNK_SIZE + blockPos.x,
	chunkPos.y * CHUNK_SIZE + blockPos.y,
	chunkPos.z * CHUNK_SIZE + blockPos.z
	};
}

