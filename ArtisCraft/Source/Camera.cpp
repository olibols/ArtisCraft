#include "Camera.h"
#include <Matrix.h>


Camera::Camera()
{
	_projectionMatrix = makeProjectionMatrix(90);
}

void Camera::update()
{
	position = _entity->position;
	rotation = _entity->rotation;

	_viewMatrix = makeViewMatrix(*this);
	_projViewMatrx = _projectionMatrix * _viewMatrix;
}

void Camera::hookEntity(const Entity & entity)
{
	_entity = &entity;
}

const glm::mat4 Camera::getViewMatrix()
{
	return glm::mat4();
}

const glm::mat4 Camera::getProjMatrix()
{
	return glm::mat4();
}

const glm::mat4 Camera::getProjViewMatrix()
{
	return _projViewMatrx;
}
