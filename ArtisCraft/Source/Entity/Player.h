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

	glm::vec3 _velocity = {0, 0, 0};
};