#pragma once

#include "ChunkManager.h"
#include "../Renderer/MasterRenderer.h"
#include "../Application.h"
#include "Terrain/WorldTerrain.h"

#include <thread>
#include <mutex>

class World {
public:
	World(Camera& camera);

	void loadChunks(Camera& camera);
	void loadChunk(sf::Vector3i pos);

	void processUpdates();

	void render(MasterRenderer& renderer);

	void setBlock(int x, int y, int z, BlockID block);
	void psetBlock(int x, int y, int z, BlockID block);
	BlockID getBlock(int x, int y, int z);

private:
	ChunkManager m_chunkManager;
	WorldTerrain m_worldTerrain;

	std::vector<Chunk*> m_chunkUpdates;

	sf::Vector3i m_currentChunk;

	bool m_mapChanged;

	int m_seed;
	int m_loadDistance = 0;

	std::thread m_chunkLoadThread;
	std::thread m_chunkUpdateThread;
	std::mutex m_mutex;
};