#pragma once
#include <GLM.h>
#include <SFML\Graphics.hpp>

#include "SFMLRenderer.h"

class MasterRenderer {
public:
	
	void drawSFML(sf::Drawable& drawable);

	void finishRender(sf::RenderWindow& window);

private:

	SFMLRenderer m_SFMLRenderer;

};