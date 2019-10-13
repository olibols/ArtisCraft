#pragma once
#include <SFML/Graphics.hpp>
#include "../MasterRenderer.h"

class FrameCounter {
public:
	FrameCounter();

	void update();

	void draw(MasterRenderer& renderer);
private:
	sf::Text m_text;
	sf::Font m_font;

	sf::Clock m_delayTimer;
	sf::Clock m_fpsTimer;
	float m_fps = 0;
	int m_frameCount = 0;
};