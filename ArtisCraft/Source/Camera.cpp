#include "Camera.h"
#include <Matrix.h>

Camera::Camera() {
	m_projectionMatrix = makeProjectionMatrix(90);

	position = { 0, 0, -3.5 };
}

void Camera::update() {
	position = m_pEntity->position;
	rotation = m_pEntity->rotation;

	m_viewMatrix = makeViewMatrix(*this);
	m_projectionViewMatrix = m_projectionViewMatrix * m_viewMatrix;
}

void Camera::hookEntity(Entity& entity) {
	m_pEntity = &entity;
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

glm::mat4 Camera::getProjectionMatrix()
{
	return m_projectionMatrix;
}

glm::mat4 Camera::getProjectionViewMatrix()
{
	return m_projectionViewMatrix;
}
