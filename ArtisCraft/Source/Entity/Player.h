#pragma once

#include "Entity.h"
#include "AABB.h"

#include <SFML/Graphics.hpp>

class World;

class Player : public Entity {
public:
	Player();

	void handleInput(sf::RenderWindow& window);

	void update(float deltaTime, World& world);
	void collide(World& world, glm::vec3 velocity, float deltaTime);
private:

	void mouseInput(sf::RenderWindow& window);
	void keyboardInput();

	AABB m_box;
	bool m_onGround = false;
};