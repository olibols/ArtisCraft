#include "Player.h"
#include "../World/World.h"

Player::Player() : Entity({0, 100, 0}, {90, 0, 0}), m_box({ 0.3f, 1.f, 0.3f })
{
}

void Player::handleInput(sf::RenderWindow & window)
{
	keyboardInput();
	mouseInput(window);
}

void Player::collide(World & world, glm::vec3 vel, float deltaTime)
{
	for(int x = position.x - m_box.dimensions.x; x < position.x + m_box.dimensions.x; x++)
	for(int y = position.y - m_box.dimensions.y; y < position.y + 0.7; y++)
	for (int z = position.z - m_box.dimensions.z; z < position.z + m_box.dimensions.z; z++) {
		auto block = world.getBlock(x, y, z);

		if (block != BlockID::Air) {
			if (vel.y > 0) {
				position.y = y - m_box.dimensions.y;
				velocity.y = 0;
			}
			else if (vel.y < 0) {
				m_onGround = true;
				position.y = y + m_box.dimensions.y + 1;
				velocity.y = 0;
			}
		}
	}
}

void Player::update(float deltaTime, World& world)
{
	velocity.x *= 0.9;
	velocity.z *= 0.9;
	//velocity.y *= 0.9;

	if (!m_onGround) {
		velocity.y -= 20.0 * deltaTime;
	}

	position.x += velocity.x * deltaTime;
	position.z += velocity.z * deltaTime;
	position.y += velocity.y * deltaTime;

	//printf("%f, %f, %f \n", position.x, position.y, position.z);
}

void Player::mouseInput(sf::RenderWindow & window)
{
	static auto const BOUND = 90;
	static auto lastMousePosition = sf::Mouse::getPosition(window);
	auto change = sf::Mouse::getPosition() - lastMousePosition;

	rotation.y += change.x * 0.03;
	rotation.x += change.y * 0.03;

	if (rotation.x > BOUND) rotation.x = BOUND;
	else if (rotation.x < -BOUND) rotation.x = -BOUND;

	if (rotation.y > 360) rotation.y = 0;
	else if (rotation.y < 0) rotation.y = 360;

	auto cx = static_cast<int>(window.getSize().x / 2);
	auto cy = static_cast<int>(window.getSize().y / 2);

	sf::Mouse::setPosition({ cx, cy }, window);

	lastMousePosition = sf::Mouse::getPosition();
}

void Player::keyboardInput()
{
	glm::vec3 change = { 0, 0, 0 };
	float speed = 7;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
		speed = 20.0;
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
		change.y = speed;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		change.y = -speed;
	}

	velocity += change;
}
