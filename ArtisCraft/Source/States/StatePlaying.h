#pragma once
#include "StateBase.h"
#include "../Renderer/MasterRenderer.h"
#include "../Entity/Player.h"

#include "../World/Chunk/Chunk.h"

#include <SFML/Graphics.hpp>

class Application;

class StatePlaying : public StateBase {
public:
	StatePlaying(Application& app);

	void update(float deltaTime) override;
	void render(MasterRenderer& renderer) override;
	void handleInput(MasterRenderer& renderer) override;

private:
	Player m_player;

	Chunk m_chunk;

};