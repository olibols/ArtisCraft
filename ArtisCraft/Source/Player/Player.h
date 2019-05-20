#pragma once
#include "../Entity.h"
#include <SFML/Graphics.hpp>

class Player : public Entity
{
public:
	Player();
	
	void handleInput(sf::RenderWindow& window);

	void update(float delataTime);

private:
	void keyboardInput();
	void mouseInput(sf::RenderWindow& window);


	glm::vec3 m_velocity;
};

