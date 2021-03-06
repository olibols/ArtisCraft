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
#include "Generators/WorldTerrain.h"

class World {
public:
	World(Camera& camera);

	ChunkBlock getBlock(int x, int y, int z);
	void setBlock(int x, int y, int z, ChunkBlock block);

	void update(Camera& camera);
	void updateRegion(int blockX, int blockY, int blockZ);

	void loadRegions(Camera& camera);

	void render(RenderMaster& renderer, Camera& camera);

	inline ChunkManager& getChunkManager() { return _chunkManager; };

	inline int getSeed() { return _worldSeed; };

	template<typename T, typename... Args>
	void addEvent(Args&&... args){
		_events.push_back(std::make_unique<T>(std::forward<Args>(args)...));
	}

	inline WorldTerrain& getWorldTerrain() { return *_worldTerrain; };

	static VectorXZ getBlockXZ(int x, int z);
	static VectorXZ getChunkXZ(int x, int z);

private:

	int _currentLoadDistance = 2;

	WorldTerrain* _worldTerrain;

	int _worldSeed = 1;

	void updateRegions();

	std::vector<std::unique_ptr<BaseWorldEvent>> _events;
	std::unordered_map<sf::Vector3i, Chunk*> _regionUpdates;

	ChunkManager _chunkManager;

	std::atomic<bool> _isRunning{ true };
	std::vector<std::thread> _chunkLoadThreads;
	std::vector<std::thread> _regionUpdateThreads;
	std::mutex _mutex;
	std::mutex _newmutex;
	
};