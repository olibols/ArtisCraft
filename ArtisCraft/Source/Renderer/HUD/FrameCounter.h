#pragma once
#include <SFML/Graphics.hpp>
#include "../RenderMaster.h"

class FrameCounter {
public:
	FrameCounter();

	void update();

	void draw(RenderMaster& renderer);
private:
	sf::Text _text;
	sf::Font _font;

	sf::Clock _delayTimer;
	sf::Clock _fpsTimer;
	float _fps = 0;
	int _frameCount = 0;
};