#include "Camera.h"

Camera::Camera()
{
	m_projectionMatrix = makeProjectionMatrix(90);
}

void Camera::update()
{
	m_viewMatrix = makeViewMatrix(*this);
	m_projViewMatrx = m_projectionMatrix * m_viewMatrix;
}

glm::mat4 Camera::getViewMatrix()
{
	return m_viewMatrix;
}

glm::mat4 Camera::getProjMatrix()
{
	return m_projectionMatrix;
}

glm::mat4 Camera::getProjectionViewMatrix()
{
	return m_projViewMatrx;
}

glm::vec3 Camera::getPosition()
{
	return m_worldPosition;
}

glm::vec3 Camera::getRotation()
{
	return m_rotation;
}
