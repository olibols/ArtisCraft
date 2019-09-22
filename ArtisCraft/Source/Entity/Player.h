#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class World;

class Player : public Entity {
public:
	Player();

	void handleInput(sf::RenderWindow& window);
	
	void update(float deltaTime, World& world);

	void collide(World& world, glm::vec3 vel, float deltaTime);

private:

	float _fallTime = 0.0f;

	void mouseInput(sf::RenderWindow& window);
	void keyboardInput();

	sf::Vector3i _spawnLocation = { 10, 150, 10 };

	bool _onGround = false;
};