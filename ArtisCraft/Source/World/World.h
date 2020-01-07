#pragma once

#include "ChunkManager.h"
#include "../Renderer/MasterRenderer.h"
#include "../Application.h"

#include <thread>
#include <mutex>

class World {
public:
	World(Camera& camera);

	void loadChunks(Camera& camera);

	void render(MasterRenderer& renderer);
private:
	ChunkManager m_chunkManager;

	std::vector<std::thread> m_meshBuildThreads;
	std::mutex m_mutex;
};