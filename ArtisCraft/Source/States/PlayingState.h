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

	Application * _app = nullptr;

	glm::vec3 lastPos;
	sf::Clock time;

	CubeRenderer _cubeboi;

	Player _player;
	World _world;
};