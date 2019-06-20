#include "Ray.h"

Ray::Ray(glm::vec3 position, glm::vec3 direction) : _startPos(position), _endPos(position), _direction(direction)
{
}

void Ray::step(float amount)
{
	float yaw = glm::radians(_direction.y + 90);
	float pitch = glm::radians(_direction.x);

	glm::vec3& p = _endPos;

	p.x -= glm::cos(yaw)    * amount;
	p.z -= glm::sin(yaw)    * amount;
	p.y -= glm::tan(pitch)  * amount;
}

glm::vec3 Ray::getEnd()
{
	return _endPos;
}

float Ray::getLength()
{
	return glm::distance(_startPos, _endPos);
}
