#pragma once
#include "Chunk/ChunkBlock.h"
#include "../Renderer/RenderMaster.h"
#include "Chunk/Region.h"
#include <Utils.h>
#include "ChunkManager.h"
#include "Events/BaseWorldEvent.h"
#include <unordered_set>
#include <memory>
#include <thread>
#include <mutex>
#include <atomic>
#include <SFML/Graphics.hpp>
#include <SimplexNoise.h>

class World {
public:
	World();

	ChunkBlock getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, ChunkBlock block);

	void update(Camera& camera);
	void updateRegion(int blockX, int blockY, int blockZ);

	void render(RenderMaster& renderer, Camera& camera);

	inline ChunkManager& getChunkManager() { return _chunkManager; };

	template<typename T, typename... Args>
	void addEvent(Args&&... args){
		_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	inline int getHeight(int x, int z) { return _worldNoise->noise(x, z) * 5;};

	static VectorXZ getBlockXZ(int x, int z);
	static VectorXZ getChunkXZ(int x, int z);

private:

	int _currentLoadDistance = 2;

	void loadRegions(const Camera& camera);
	void updateRegions();

	std::vector<std::unique_ptr<BaseWorldEvent>> _events;
	std::unordered_map<sf::Vector3i, Chunk*> _regionUpdates;

	ChunkManager _chunkManager;

	std::atomic<bool> _isRunning{ true };
	std::vector<std::thread> _chunkLoadThreads;
	std::mutex _mutex;

};