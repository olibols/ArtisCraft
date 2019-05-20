#include "Camera.h"
#include <Matrix.h>

Camera::Camera() {
	m_projectionMatrix = makeProjectionMatrix(90);
}

void Camera::update() {
	position = m_pEntity->position;
	rotation = m_pEntity->rotation;

	m_viewMatrix = makeViewMatrix(*this);
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
