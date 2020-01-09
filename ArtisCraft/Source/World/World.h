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
	void buildChunks(Camera& camera);

	void render(MasterRenderer& renderer);

	void setBlock(int x, int y, int z, BlockID block);
	BlockID getBlock(int x, int y, int z);

private:
	ChunkManager m_chunkManager;
	WorldTerrain m_worldTerrain;

	int m_loadDistance = 2;

	std::vector<Chunk*> m_chunkUpdates;

	std::thread m_chunkManagementThread;
	std::thread m_meshBuildThread;
	std::mutex m_mutex;
};