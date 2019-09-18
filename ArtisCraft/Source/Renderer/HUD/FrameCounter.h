#pragma once
#include <SFML/Graphics.hpp>
#include "../RenderMaster.h"

class Entity;

class FrameCounter {
public:
	FrameCounter(Entity& entity);

	void update();

	void draw(RenderMaster& renderer);
private:
	sf::Text _text;
	sf::Font _font;

	Entity* _entity;

	sf::Clock _delayTimer;
	sf::Clock _fpsTimer;
	float _fps = 0;
	int _frameCount = 0;
};