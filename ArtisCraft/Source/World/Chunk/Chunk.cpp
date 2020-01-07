#include "Chunk.h"

#include "ChunkMeshBuilder.h"

Chunk::Chunk(sf::Vector3i pos) : m_location(pos)
{
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				setBlock(x, y, z, BlockID::Grass);
			}
		}
	}
}

void Chunk::setBlock(int x, int y, int z, BlockID block)
{
	if (isOutOfBounds(x) ||
		isOutOfBounds(y) ||
		isOutOfBounds(z)) {
		return;
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
		return BlockID::Air;
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
