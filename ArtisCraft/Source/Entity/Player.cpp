#include "Player.h"
#include <SFML/Graphics.hpp>

Player::Player() : Entity({ 5, 5, 5 }, { 0, 0, 0 })
{
}

void Player::handleInput(sf::RenderWindow& window)
{
	keyboardInput();
	mouseInput(window);
}

void Player::update(float deltaTime)
{
	_onGround = false;

	velocity.x *= 0.9;
	velocity.z *= 0.9;

	position.x += velocity.x * deltaTime;

	//position.y += velocity.y * deltaTime;

	position.z += velocity.z * deltaTime;

	//printf("Coordinates: %f, %f, %f \n Onground: %b \n", position.x, position.y, position.z, _onGround);
}

void Player::mouseInput(sf::RenderWindow& window)
{
	static auto const BOUND = 90;
	static auto lastMousePosition = sf::Mouse::getPosition(window);
	auto change = sf::Mouse::getPosition() - lastMousePosition;

	rotation.y += change.x * 0.05;
	rotation.x += change.y * 0.05;

	if (rotation.x > BOUND) rotation.x = BOUND;
	else if (rotation.x < -BOUND) rotation.x = -BOUND;

	if (rotation.y > 360) rotation.y = 0;
	else if (rotation.y < 0)    rotation.y = 360;

	auto cx = static_cast<int>(window.getSize().x / 2);
	auto cy = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({ cx, cy }, window);

	lastMousePosition = sf::Mouse::getPosition();
}

void Player::keyboardInput()
{
	glm::vec3 change = { 0, 0, 0 };
	float speed = 3.0;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		speed = 1.5;
	}

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		position.y = 150;
		velocity = { 0, 0, 0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		change.y += speed * 5;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		change.y -= speed;
	}

	velocity += change;

	//printf("Position: %f, %f, %f \n", position.x, position.y, position.z);
}