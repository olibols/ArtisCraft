#pragma once
#include "Entity.h"

#include <SFML/Graphics.hpp>

class Player : public Entity {
public:
	Player();

	void handleInput(sf::RenderWindow& window);

	void update(float deltaTime);
private:

	void mouseInput(sf::RenderWindow& window);
	void keyboardInput();

	sf::Vector3i m_spawnLocation = { 10, 150, 10 };
};