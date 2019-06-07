#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player()
{
	position = { 0, 3, 3 };
}

void Player::handleInput()
{
	keyboardInput();
	//mouseInput();
}

void Player::update(float deltaTime)
{
	position += _velocity * deltaTime;
	_velocity *= 0.95;
}


void Player::keyboardInput()
{
	glm::vec3 change = {0, 0, 0};
	float speed = 0.5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		change.x += -glm::cos(glm::radians(rotation.y + 90)) * speed;
		change.z += -glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		change.x += glm::cos(glm::radians(rotation.y + 90)) * speed;
		change.z += glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		change.x += -glm::cos(glm::radians(rotation.y)) * speed;
		change.z += -glm::sin(glm::radians(rotation.y)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		change.x += glm::cos(glm::radians(rotation.y)) * speed;
		change.z += glm::sin(glm::radians(rotation.y)) * speed;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		change.y += speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		change.y -= speed;
	}

	_velocity += change;

	printf("Position: %f, %f, %f \n", position.x, position.y, position.z);
}
