#pragma once
#include "StateBase.h"

class StateSplash : public StateBase {
public:
	StateSplash(Application& app);

	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
	void handleInput() override;

private:

};