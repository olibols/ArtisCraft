#pragma once
#include "Chunk/ChunkBlock.h"
#include "../Renderer/RenderMaster.h"
#include "Chunk/Region.h"
#include <Utils.h>
#include "ChunkManager.h"
#include "Events/BaseWorldEvent.h"
#include <unordered_set>
#include <memory>
#include <SFML/Graphics.hpp>

class World {
public:
	World();

	ChunkBlock getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, ChunkBlock block);

	void update(const Camera& camera);
	void updateRegion(int blockX, int blockY, int blockZ);

	void render(RenderMaster& renderer);

	inline ChunkManager& getChunkManager() { return _chunkManager; };

	template<typename T, typename... Args>
	void addEvent(Args&&... args){
		_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	static VectorXZ getBlockXZ(int x, int z);
	static VectorXZ getChunkXZ(int x, int z);

private:

	int _currentLoadDistance = 2;

	void updateRegions();

	std::vector<std::unique_ptr<BaseWorldEvent>> _events;
	std::unordered_map<sf::Vector3i, Chunk*> _regionUpdates;

	ChunkManager _chunkManager;
};