#pragma once

#include <SFML/Graphics.hpp>
#include <GLM.h>
#include <memory>
#include "BaseWorldEvent.h"

class Player;

class PlayerDigEvent : public BaseWorldEvent {
public:
	PlayerDigEvent(sf::Mouse::Button button, const glm::vec3& location, Player& player);

	void handle(World& world);

private:
	void dig(World& world);

	sf::Mouse::Button _buttonPress;
	glm::vec3 _digSpot;
	Player* _player;
};