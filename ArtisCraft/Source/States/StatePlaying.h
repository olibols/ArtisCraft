#pragma once
#include "StateBase.h"

#include <SFML/Graphics.hpp>

class StatePlaying : public StateBase {
public:
	StatePlaying(Application& app);

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void handleInput() override;

private:

};