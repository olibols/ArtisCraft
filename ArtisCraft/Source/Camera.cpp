#include "Camera.h"
#include <SFML/Graphics.hpp>

glm::mat4 makeViewMatrix(Camera& camera)
{
	glm::mat4 matrix = glm::mat4(1.0f);

	matrix = glm::rotate(matrix, glm::radians(camera.rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(camera.rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, -camera.position);

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
	_projMatrix = glm::perspective(glm::radians(90.0f), 1920.0f / 1080.0f, 0.1f, 1000.0f);
}

void Camera::update()
{
	position = _entity->position;
	rotation = _entity->rotation;

	_viewMatrix = makeViewMatrix(*this);
	
	_projViewMatrix = _projMatrix * _viewMatrix;
}

void Camera::hookEntity(const Entity & entity)
{
	_entity = &entity;
}

void Camera::newFov(float value)
{
	_projMatrix = glm::perspective(glm::radians(value), 1920.0f / 1080.0f, 0.1f, 1000.0f);
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

