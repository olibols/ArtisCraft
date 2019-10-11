#pragma once
#include "StateBase.h"

#include "../Entity/Player.h"

class PlayingState : public StateBase {
public:
	PlayingState(Application& app);

	void handleEvent(sf::Event event) override;
	void handleInput() override;

	void update(float deltaTime) override;

	void render() override;

private:
	glm::vec3 m_lastPos;
	sf::Clock m_time;

	Player m_player;
};