#include "Ray.h"

Ray::Ray(glm::vec3 position, glm::vec3 direction) : m_startPos(position), m_endPos(position), m_direction(direction)
{
}

void Ray::step(float amount)
{
	float yaw = glm::radians(m_direction.y + 90);
	float pitch = glm::radians(m_direction.x);

	glm::vec3& p = m_endPos;

	p.x -= glm::cos(yaw)    * amount;
	p.z -= glm::sin(yaw)    * amount;
	p.y -= glm::tan(pitch)  * amount;
}

glm::vec3 Ray::getEnd()
{
	return m_endPos;
}

float Ray::getLength()
{
	return glm::distance(m_startPos, m_endPos);
}