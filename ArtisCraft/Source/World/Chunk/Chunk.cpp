#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../ChunkManager.h"

Chunk::Chunk(sf::Vector3i pos, ChunkManager& cm) : m_location(pos), m_chunkManager(&cm)
{
	for (auto& block : m_blocks) {
		block = BlockID::Air;
	}
}

void Chunk::setBlock(int x, int y, int z, BlockID block)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		auto pos = toGlobalBlockPos({ x,y,z }, m_location);
		m_chunkManager->setBlock(pos, block);
	}
	m_hasMesh = false;
	m_isBuffered = false;
	m_blocks[getIndex(x, y, z)] = block;
}

BlockID Chunk::getBlock(int x, int y, int z)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		auto pos = toGlobalBlockPos({ x,y,z }, m_location);
		return m_chunkManager->getBlock(pos);
	}
	return m_blocks[getIndex(x, y, z)];
}

sf::Vector3i Chunk::getLocation()
{
	return m_location;
}

void Chunk::buildMesh()
{
	m_mesh = buildChunkMesh(*this);
	m_hasMesh = true;
	m_isBuffered = false;
}

void Chunk::bufferMesh()
{
	m_mesh.bufferMesh();
	m_isBuffered = true;
}

ChunkMesh & Chunk::getMesh()
{
	return m_mesh;
}

bool Chunk::hasMesh()
{
	return m_hasMesh;
}

bool Chunk::isLoaded()
{
	return m_isLoaded;
}

void Chunk::setLoaded()
{
	m_isLoaded = true;
}

void Chunk::draw(MasterRenderer & renderer)
{
	if (m_hasMesh) {
		if (!m_isBuffered)
			bufferMesh();
		renderer.drawChunk(m_mesh);
	}
}

int Chunk::getIndex(int x, int y, int z)
{
	return y * CHUNK_AREA + z * CHUNK_SIZE + x;
}

bool Chunk::isOutOfBounds(int index)
{
	return  index >= CHUNK_SIZE || index < 0;
}
