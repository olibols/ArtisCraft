#pragma once
#include "BaseState.h"

#include "../Entity/Player.h"
#include "../World/Block/Chunk/Chunk.h"

class PlayingState : public BaseState {
public:
	PlayingState(Application& app);

	void handleEvent(sf::Event event) override;
	void handleInput() override;

	void update(float deltaTime) override;

	void render(RenderMaster& renderer) override;

private:
	Player _player;
	
	Chunk _chunk;
};