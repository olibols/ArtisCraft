#include "ChunkManager.h"
#include "Chunk/ChunkTools.h"

Chunk& ChunkManager::addChunk(sf::Vector3i pos)
{
	auto itr = m_chunks.find(pos);
	if (itr == m_chunks.cend()) {
		return m_chunks.emplace(std::piecewise_construct, std::forward_as_tuple(pos), std::forward_as_tuple(pos, *this)).first->second;
	}
	return itr->second;
}

Chunk & ChunkManager::getChunk(sf::Vector3i pos)
{
	auto itr = m_chunks.find(pos);
	if (itr == m_chunks.cend()) {
		static Chunk errchunk({ 0, 0, 0 }, *this);
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
	return itr->second.getBlock(chunkPos.x, chunkPos.y, chunkPos.z);
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
	ChunkTools::fillChunk(addChunk(cp), terrain);
	ChunkTools::fillChunk(addChunk({ cp.x, cp.y + 1, cp.z }), terrain);
	ChunkTools::fillChunk(addChunk({ cp.x, cp.y - 1, cp.z }), terrain);
	ChunkTools::fillChunk(addChunk({ cp.x - 1, cp.y, cp.z }), terrain);
	ChunkTools::fillChunk(addChunk({ cp.x + 1, cp.y, cp.z }), terrain);
	ChunkTools::fillChunk(addChunk({ cp.x, cp.y, cp.z - 1 }), terrain);
	ChunkTools::fillChunk(addChunk({ cp.x, cp.y, cp.z + 1 }), terrain);
}

void ChunkManager::updateLoadList(Camera & cam)
{
	sf::Vector3i pos = toChunkPos({ (int)cam.position.x, (int)cam.position.y, (int)cam.position.z, });
	
	for (int x = pos.x - 2; x < pos.x + 2; x++) {
		for (int y = pos.y - 2; y < pos.y + 2; y++) {
			for (int z = pos.z - 2; z < pos.z + 2; z++) {
				addChunk({ x,y,z });
			}
		}
	}
}

void ChunkManager::updateSetupList(Camera & cam, WorldTerrain& terrain)
{

}

void ChunkManager::updateRenderList(Camera & cam)
{
}

std::vector<Chunk*>& ChunkManager::getLoadlist()
{
	return m_loadList;
}

std::vector<Chunk*>& ChunkManager::getSetuplist()
{
	return m_setupList;
}

std::vector<Chunk*>& ChunkManager::getRenderlist()
{
	return m_renderlist;
}

ChunkPosMap<Chunk>& ChunkManager::getChunks()
{
	return m_chunks;
}
