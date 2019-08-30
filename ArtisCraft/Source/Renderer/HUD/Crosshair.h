#pragma once
#include <SFML/Graphics.hpp>
#include "../RenderMaster.h"
#include "../../Settings.h"

class Crosshair {
public:
	Crosshair();

	void draw(RenderMaster& renderer);
private:

	sf::Texture texture;
	sf::Sprite sprite;

};