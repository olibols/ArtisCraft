#include "Crosshair.h"

Crosshair::Crosshair()
{
	texture.loadFromFile("../Resources/Textures/crosshair.png");

	sprite.setTexture(texture);

	sf::Vector2u size = texture.getSize();

	sprite.setPosition(Settings::width / 2 - size.x / 2, Settings::height / 2 - size.y / 2);
}

void Crosshair::draw(RenderMaster & renderer)
{
	renderer.drawSFML(sprite);
}
