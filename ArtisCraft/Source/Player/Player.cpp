#include "Player.h"

Player::Player()
{
	position = { 0, 0, -5 };
}

void Player::handleInput(const sf::RenderWindow & window)
{
	keyboardInput();
	mouseInput(window);
}

void Player::update(float deltaTime)
{
	position += _velocity * deltaTime;
	_velocity *= 0.9;
}

void Player::keyboardInput()
{
	glm::vec3 change = {0, 0, 0};
	float speed = 0.5;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		change.x = glm::cos(glm::radians(rotation.y + 90)) * speed;
		change.z = glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		change.x = -glm::cos(glm::radians(rotation.y + 90)) * speed;
		change.z = -glm::sin(glm::radians(rotation.y + 90)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		change.x = glm::cos(glm::radians(rotation.y)) * speed;
		change.z = glm::sin(glm::radians(rotation.y)) * speed;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		change.x = -glm::cos(glm::radians(rotation.y)) * speed;
		change.z = -glm::sin(glm::radians(rotation.y)) * speed;
	}

	_velocity += change;
}


void Player::mouseInput(const sf::RenderWindow & window)
{
	static int viewLock = 80;
	auto lastPosition = sf::Mouse::getPosition(window);
	auto positionChange = sf::Mouse::getPosition(window) - lastPosition;

	rotation.x += positionChange.x * 0.05;
	rotation.y += positionChange.y * 0.05;

	if (rotation.y > 360) rotation.y = 0;
	else if (rotation.y < 0)    rotation.y = 360;

	auto cx = static_cast<int>(window.getSize().x / 2);
	auto cy = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({ cx, cy }, window);

	lastPosition = sf::Mouse::getPosition();
}
