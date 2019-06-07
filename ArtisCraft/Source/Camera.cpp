#include "Camera.h"
#include <SFML/Graphics.hpp>

glm::mat4 makeViewMatrix(glm::vec3 rot, glm::vec3 pos)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, glm::radians(rot.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rot.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rot.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, pos);

	return matrix;
}

glm::mat4 makeModelMatrix(glm::vec3 position, glm::vec3 rotation)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, position);

	return matrix;
}

Camera::Camera()
{
	_projMatrix = glm::perspective(glm::radians(90.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

void Camera::update()
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		_worldPosition.x += 0.1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		_worldPosition.x -= 0.1;
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		_worldPosition.z += 0.1;
	}if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		_worldPosition.z -= 0.1;
	}


	_viewMatrix = glm::lookAt(
		_worldPosition,
		glm::vec3(0, 0, 0), 
		glm::vec3(0, 1, 0)  
	);
	_projViewMatrix = _projMatrix * _viewMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return _viewMatrix;
}

glm::mat4 Camera::getProjMatrix()
{
	return _projMatrix;
}

glm::mat4 Camera::getProjViewMatrix()
{
	return _projViewMatrix;
}

glm::vec3 Camera::getPosition()
{
	return _worldPosition;
}

glm::vec3 Camera::getRotation()
{
	return _rotation;
}
