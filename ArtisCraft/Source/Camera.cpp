#include "Camera.h"
#include "Util/Matrix.h"

Camera::Camera()
{
	m_projectionMatrix = makeProjectionMatrix(90);

	position = { 0, 0, -3.5 };
}

void Camera::update()
{
	m_viewMatrix = makeViewMatrix(*this);
	m_projViewMatrx = m_projectionMatrix * m_viewMatrix;
}

void Camera::hookEntity(const Entity& entity)
{
	m_pEntity = &entity;
}

const glm::mat4& Camera::getViewMatrix() const noexcept
{
	return m_viewMatrix;
}

const glm::mat4& Camera::getProjMatrix() const noexcept
{
	return m_projectionMatrix;
}

const glm::mat4& Camera::getProjectionViewMatrix() const noexcept
{
	return m_projViewMatrx;
}
