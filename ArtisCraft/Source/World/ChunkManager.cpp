#include "ChunkManager.h"

void ChunkManager::addChunk(sf::Vector3i pos)
{
	auto itr = m_chunks.find(pos);
	if (itr == m_chunks.cend()) {
		m_chunks.emplace(pos);
	}
	return;
}

Chunk & ChunkManager::getChunk(sf::Vector3i pos)
{
	auto itr = m_chunks.find(pos);
	if (itr == m_chunks.cend()) {
		static Chunk errchunk({ 0, 0, 0 });
		return errchunk;
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
}

void ChunkManager::setBlock(sf::Vector3i pos, BlockID block)
{
	sf::Vector3i chunkPos = toChunkPos(pos);
	auto itr = m_chunks.find(chunkPos);
	if (itr != m_chunks.cend()) {
		itr->second.setBlock(toLocalBlockPos(pos).x, toLocalBlockPos(pos).y, toLocalBlockPos(pos).z, block);
	}
	assert(itr != m_chunks.end());
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

void ChunkManager::buildNeighbours(sf::Vector3i pos)
{
	const auto &cp = pos;
	addChunk(cp);
	addChunk({ cp.x, cp.y + 1, cp.z });
	addChunk({ cp.x, cp.y - 1, cp.z });
	addChunk({ cp.x - 1, cp.y, cp.z });
	addChunk({ cp.x + 1, cp.y, cp.z });
	addChunk({ cp.x, cp.y, cp.z - 1 });
	addChunk({ cp.x, cp.y, cp.z + 1 });
}

ChunkPosMap<Chunk>& ChunkManager::getChunks()
{
	return m_chunks;
}
