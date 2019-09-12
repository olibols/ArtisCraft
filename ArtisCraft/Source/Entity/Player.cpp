#include "Player.h"
#include "../World/World.h"
#include <SFML/Graphics.hpp>

Player::Player() : Entity({10, 150, 10}, {0, 0, 0}, {0.25, 1.5, 0.25})
{
}

void Player::handleInput(sf::RenderWindow& window)
{
	keyboardInput();
	mouseInput(window);
}

void Player::update(float deltaTime, World& world)
{
	if (!_onGround) {
		velocity.y -= 5.0 * deltaTime;
	}
	_onGround = false;

	hitbox.update(position);
	velocity.x *= 0.9;
	velocity.z *= 0.9;

	position.x += velocity.x * deltaTime;
	collide(world, { velocity.x, 0, 0 }, deltaTime);

	position.y += velocity.y * deltaTime;
	collide(world, { 0, velocity.y, 0 }, deltaTime);

	position.z += velocity.z * deltaTime;
	collide(world, { 0, 0, velocity.z }, deltaTime);

	//printf("Coordinates: %f, %f, %f \n Onground: %b \n", position.x, position.y, position.z, _onGround);
}

void Player::collide(World& world, glm::vec3 vel, float dt)
{
	for (int x = position.x - hitbox.dimensions.x; x < position.x + hitbox.dimensions.x; x++)
		for (int y = position.y - hitbox.dimensions.y; y < position.y; y++)
			for (int z = position.z - hitbox.dimensions.z; z < position.z + hitbox.dimensions.z; z++)
			{
				auto block = world.getBlock(x, y, z);

				if (block != 0)
				{
					if (vel.y > 0)
					{
						position.y -= 0.01;
						velocity.y = 0;
					}
					else if (vel.y < 0) {
						position.y = y + hitbox.dimensions.y + 1;
						velocity.y = 0;
						_onGround = true;
					}

					if (vel.x > 0)
					{
						position.x = x - hitbox.dimensions.x;
					}
					else if (vel.x < 0)
					{
						position.x = x + hitbox.dimensions.x + 1;
					}

					if (vel.z > 0)
					{
						position.z = z - hitbox.dimensions.z;
					}
					else if (vel.z < 0)
					{
						position.z = z + hitbox.dimensions.z + 1;
					}
				}
			}
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
	glm::vec3 change = {0, 0, 0};
	float speed = 0.5;

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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && _onGround)
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
