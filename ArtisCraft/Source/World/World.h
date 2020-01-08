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

	void render(MasterRenderer& renderer);

	void setBlock(int x, int y, int z, BlockID block);
	BlockID getBlock(int x, int y, int z);
private:
	ChunkManager m_chunkManager;
	WorldTerrain m_worldTerrain;

	std::vector<std::thread> m_meshBuildThreads;
	std::mutex m_mutex;
};