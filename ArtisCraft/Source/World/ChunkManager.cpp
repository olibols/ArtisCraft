#include "ChunkManager.h"
#include "Chunk/ChunkTools.h"
#include "Terrain/WorldTerrain.h"

ChunkManager::ChunkManager(WorldTerrain& terrain) : m_terrain(&terrain)
{
}

Chunk& ChunkManager::addChunk(sf::Vector3i pos)
{
	auto itr = m_chunks.find(pos);
	if (itr == m_chunks.cend()) {
		return m_chunks.emplace(std::piecewise_construct, std::forward_as_tuple(pos), std::forward_as_tuple(pos, *this)).first->second;
	}
	return itr->second;
}

Column& ChunkManager::addColumn(sf::Vector2i pos)
{
	auto itr = m_heightMap.find(pos);
	if (itr == m_heightMap.cend()) {
		return m_heightMap.emplace().first->second;
	}
	return itr->second;
}

void ChunkManager::makeMesh(sf::Vector3i pos)
{
	for(int nx = -1; nx <= 1; nx++)
	for(int ny = -1; ny <= 1; ny++)
		for (int nz = -1; nz <= 1; nz++) {
			m_terrain->buildChunk(&addChunk({ pos.x + nx, pos.y + ny, pos.z + nz }));
	}
	getChunk(pos).buildMesh();
}

void ChunkManager::loadChunk(sf::Vector3i pos)
{
	m_terrain->buildChunk(&getChunk(pos));
}

Chunk & ChunkManager::getChunk(sf::Vector3i pos)
{
	auto itr = m_chunks.find(pos);
	if (itr == m_chunks.cend()) {
		return addChunk(pos);
	}
	return itr->second;
}

BlockID ChunkManager::getBlock(sf::Vector3i pos)
{
	sf::Vector3i chunkPos = toChunkPos(pos);
	auto itr = m_chunks.find(chunkPos);
	if (itr == m_chunks.cend()) {
		return BlockID::ERR_TYPE;
	}
	sf::Vector3i locPos = toLocalBlockPos(pos);
	return itr->second.getBlock(locPos.x, locPos.y, locPos.z);
}

void ChunkManager::setBlock(sf::Vector3i pos, BlockID block)
{
	sf::Vector3i chunkPos = toChunkPos(pos);
	auto itr = m_chunks.find(chunkPos);
	if (itr != m_chunks.cend()) {
		itr->second.setBlock(toLocalBlockPos(pos).x, toLocalBlockPos(pos).y, toLocalBlockPos(pos).z, block);
	}
}

bool ChunkManager::hasChunk(sf::Vector3i pos)
{
	return m_chunks.find(pos) != m_chunks.cend();
}

bool ChunkManager::hasNeighbours(sf::Vector3i pos)
{
	const auto &cp = pos;
	return hasChunk(pos) &&
		hasChunk({ cp.x, cp.y + 1, cp.z }) &&
		hasChunk({ cp.x, cp.y - 1, cp.z }) &&
		hasChunk({ cp.x - 1, cp.y, cp.z }) &&
		hasChunk({ cp.x + 1, cp.y, cp.z }) &&
		hasChunk({ cp.x, cp.y, cp.z - 1 }) &&
		hasChunk({ cp.x, cp.y, cp.z + 1 });
}

void ChunkManager::buildNeighbours(sf::Vector3i pos, WorldTerrain& terrain)
{
	const auto &cp = pos;
	terrain.buildChunk(&addChunk(cp));
	terrain.buildChunk(&addChunk({ cp.x, cp.y + 1, cp.z }));
	terrain.buildChunk(&addChunk({ cp.x, cp.y - 1, cp.z }));
	terrain.buildChunk(&addChunk({ cp.x - 1, cp.y, cp.z }));
	terrain.buildChunk(&addChunk({ cp.x + 1, cp.y, cp.z }));
	terrain.buildChunk(&addChunk({ cp.x, cp.y, cp.z - 1 }));
	terrain.buildChunk(&addChunk({ cp.x, cp.y, cp.z + 1 }));
}

ChunkPosMap<Chunk>& ChunkManager::getChunks()
{
	return m_chunks;
}
