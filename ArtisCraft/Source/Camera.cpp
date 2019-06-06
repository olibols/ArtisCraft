#include "Camera.h"

glm::mat4 makeViewMatrix(glm::vec3 rot, glm::vec3 pos)
{
	glm::mat4 matrix;

	matrix = glm::rotate(matrix, glm::radians(rot.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rot.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rot.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, pos);

	return matrix;
}

glm::mat4 makeModelMatrix(glm::vec3 position, glm::vec3 rotation)
{
	glm::mat4 matrix;

	matrix = glm::rotate(matrix, glm::radians(rotation.x), { 1, 0, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.y), { 0, 1, 0 });
	matrix = glm::rotate(matrix, glm::radians(rotation.z), { 0, 0, 1 });

	matrix = glm::translate(matrix, position);

	return matrix;
}

Camera::Camera()
{
	_projMatrix = glm::perspective(90.0f, 1280.0f / 720.0f, 0.1f, 1000.0f);
}

void Camera::update()
{
	_viewMatrix = makeViewMatrix(_rotation, _worldPosition);
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
