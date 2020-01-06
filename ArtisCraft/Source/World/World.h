#pragma once

#include "ChunkManager.h"
#include "../Renderer/MasterRenderer.h"

class World {
public:
	World();

	void render(MasterRenderer& renderer);
private:

	ChunkManager m_chunkManager;
};