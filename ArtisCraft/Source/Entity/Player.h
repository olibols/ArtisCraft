#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class World;

class Player : public Entity {
public:
	Player();

	void handleInput(sf::RenderWindow& window);

	void update(float deltaTime);

private:

	float _fallTime = 0.0f;

	void mouseInput(sf::RenderWindow& window);
	void keyboardInput();

	sf::Vector3i _spawnLocation = { 5, 5, 5 };

	bool _onGround = false;
};