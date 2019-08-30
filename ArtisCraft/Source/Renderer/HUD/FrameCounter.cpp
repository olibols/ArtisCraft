#include "FrameCounter.h"

FrameCounter::FrameCounter(Entity& entity)
{
	_entity = &entity;

	_text.move(10, 10);
	_text.setOutlineColor(sf::Color::Black);
	_text.setOutlineThickness(2);

	_font.loadFromFile("../Resources/Fonts/rs.ttf");
	_text.setFont(_font);
	_text.setCharacterSize(25);
}

void FrameCounter::update()
{
	_frameCount++;
	if (_delayTimer.getElapsedTime().asSeconds() > 0.5)
	{
		_fps = _frameCount / _fpsTimer.restart().asSeconds();

		_frameCount = 0;
		_delayTimer.restart();
	}
}

void FrameCounter::draw(RenderMaster& renderer)
{
	_text.setString("FPS: " + std::to_string(_fps) + " Position: " + std::to_string(_entity->position.x) + " " + std::to_string(_entity->position.y) + " " + std::to_string(_entity->position.z));
	renderer.drawSFML(_text);
}
