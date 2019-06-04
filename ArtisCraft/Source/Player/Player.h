#pragma once
#include <SFML/Graphics.hpp>

#include "../Entity.h"

class Player : public Entity {
public:
	Player();

	void handleInput(const sf::RenderWindow& window);

	void update(float deltaTime);

private:
	void keyboardInput();

	void mouseInput(const sf::RenderWindow& window);

	glm::vec3 _velocity;
};