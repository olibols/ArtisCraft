#include "Player.h"
#include "../World/World.h"

Player::Player() : Entity({0, 100, 0}, {90, 0, 0}), m_box({ 0.25, 3.5, 0.25 })
{
}

void Player::handleInput(sf::RenderWindow & window)
{
	keyboardInput();
	mouseInput(window);
}

// This is called after the movement code is called and handles collisions
void Player::collide(World & world, glm::vec3 vel, float deltaTime)
{
	world.loadChunk(toChunkPos({ (int)position.x, (int)position.y, (int)position.z})); // To prevent errors, load the current chunk

	for(int x = position.x - m_box.dimensions.x; x < position.x + m_box.dimensions.x; x++)
	for(int y = position.y - m_box.dimensions.y; y < position.y + 0.3; y++)
	for(int z = position.z - m_box.dimensions.z; z < position.z + m_box.dimensions.z; z++) {
		auto block = world.getBlock(x, y, z);

		if (block != BlockID::Air) { // If we are intersecting with another block, move us out of that block
			if (vel.y > 0) {
				velocity.y = 0;
				position.y -= 0.1;
			}
			else if (vel.y < 0) {
				m_onGround = true;
				position.y = y + m_box.dimensions.y + 1;
				velocity.y = 0;
			}

			if (vel.x > 0) {
				position.x = x - m_box.dimensions.x;
			}
			else if (vel.x < 0) {
				position.x = x + m_box.dimensions.x + 1;
			}

			if (vel.z > 0) {
				position.z = z - m_box.dimensions.z;
			}
			else if (vel.z < 0) {
				position.z = z + m_box.dimensions.z + 1;
			}
		}
	}
}

// This is called every frame and handles the movement after keys have been pressed etc
void Player::update(float deltaTime, World& world)
{
	m_timeAlive += deltaTime;

	if (m_timeAlive > 5.0) { // Only handle movement and physics after 5 seconds

		if (!m_onGround) {
			velocity.y -= 40.0 * deltaTime;
		}
		m_onGround = false;

		m_box.update(position);
		velocity.x *= 0.9;
		velocity.z *= 0.9;

		position.y += velocity.y * deltaTime;
		collide(world, { 0, velocity.y, 0 }, deltaTime);

		position.x += velocity.x * deltaTime;
		collide(world, { velocity.x, 0, 0 }, deltaTime);

		position.z += velocity.z * deltaTime;
		collide(world, { 0, 0, velocity.z }, deltaTime);
	}

}

// This function takes in the mouse input and creates a rotation vector based on how it moved since last frame.
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

// This handles keypresses and does actions based on what was pressed. It creates a movement vector.
void Player::keyboardInput()
{
	glm::vec3 change = { 0, 0, 0 };
	float speed = 3.0;

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
		position.y = 250;
		velocity = { 0, 0, 0 };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && m_onGround)
	{
		change.y = speed * 6;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		change.y = -speed;
	}

	velocity += change;
}
