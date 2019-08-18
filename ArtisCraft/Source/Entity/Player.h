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
	void mouseInput(sf::RenderWindow& window);
	void keyboardInput();

	bool _onGround = false;
};