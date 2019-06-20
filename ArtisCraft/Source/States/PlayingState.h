#pragma once
#include "BaseState.h"
#include "../Renderer/CubeRenderer.h"

#include "../Entity/Player.h"
#include "../World/World.h"

class PlayingState : public BaseState {
public:
	PlayingState(Application& app);

	void handleEvent(sf::Event event) override;
	void handleInput() override;

	void update(float deltaTime) override;

	void render(RenderMaster& renderer) override;

private:

	glm::vec3 lastPos;

	CubeRenderer _cuberenderer;

	Player _player;
	
	World _world;
};