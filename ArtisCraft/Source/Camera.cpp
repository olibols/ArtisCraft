#include "Camera.h"

#include <gtc/matrix_transform.hpp>
#include <glm.hpp>
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
	m_projMatrix = glm::perspective(glm::radians((float)90), (float)1280 / (float)720, 0.1f, 1000.0f);
}

void Camera::update()
{
	position = m_entity->position;
	rotation = m_entity->rotation;

	m_viewMatrix = makeViewMatrix(*this);

	m_projViewMatrix = m_projMatrix * m_viewMatrix;
}

void Camera::hookEntity(const Entity & entity)
{
	m_entity = &entity;
}

void Camera::newFov(float value)
{
	m_projMatrix = glm::perspective(glm::radians(value), 1280.0f / 720.0f, 0.1f, 1000.0f);
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

glm::mat4 Camera::getProjMatrix()
{
	return m_projMatrix;
}

glm::mat4 Camera::getProjViewMatrix()
{
	return m_projViewMatrix;
}