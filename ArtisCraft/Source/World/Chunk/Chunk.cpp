#include "Chunk.h"

#include "ChunkMeshBuilder.h"
#include "../ChunkManager.h"

Chunk::Chunk(sf::Vector3i pos, ChunkManager& cm) : m_location(pos), m_chunkManager(&cm)
{}

void Chunk::setBlock(int x, int y, int z, BlockID block)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		auto pos = toGlobalBlockPos({ x,y,z }, m_location);
		m_chunkManager->setBlock(pos, block);
	}
	m_hasBlocks = true;
	m_blocks[getIndex(x, y, z)] = block;
	m_layers[y].update(block);
}

BlockID Chunk::getBlock(int x, int y, int z)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		auto pos = toGlobalBlockPos({ x,y,z }, m_location);
		return m_chunkManager->getBlock(pos);
	}
	return m_blocks[getIndex(x, y, z)].id;
}

Chunk & Chunk::getAdjChunk(int x, int y, int z)
{
	return m_chunkManager->getChunk({ m_location.x + x, m_location.y + y, m_location.x + z });
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

Layer Chunk::getLayer(int y)
{
	if (y == -1) {
		return m_chunkManager->getChunk({m_location.x, m_location.y - 1, m_location.z}).getLayer(CHUNK_SIZE - 1);
	}
	else if (y == CHUNK_SIZE) {
		return m_chunkManager->getChunk({ m_location.x, m_location.y + 1, m_location.z }).getLayer(0);
	}
	else {
		return m_layers[y];
	}
}

bool Chunk::isLoaded()
{
	return m_isLoaded;
}

void Chunk::setLoaded()
{
	m_isLoaded = true;
}

bool Chunk::isSeeded()
{
	return m_isSeeded;
}

void Chunk::setSeeded()
{
	m_isSeeded = true;
}

bool Chunk::hasBlocks()
{
	return m_hasBlocks;
}

void Chunk::draw(MasterRenderer & renderer)
{
	if (m_hasMesh && m_isLoaded) {
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
