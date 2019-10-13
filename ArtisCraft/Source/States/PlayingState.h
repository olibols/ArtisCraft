#pragma once
#include "StateBase.h"

#include "../Entity/Player.h"
#include "../Renderer/HUD/FrameCounter.h"

class PlayingState : public StateBase {
public:
	PlayingState(Application& app);

	void handleEvent(sf::Event event) override;
	void handleInput() override;

	void update(float deltaTime) override;

	void render(MasterRenderer& renderer) override;

	void onOpen() override;

private:
	glm::vec3 m_lastPos;
	sf::Clock m_time;

	FrameCounter m_frameCounter;

	Player m_player;
};