#include "Util/GLM.h"


class Camera
{
public:
	Camera();

	void update();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjMatrix();
	glm::mat4 getProjectionViewMatrix();

	glm::vec3 getPosition();
	glm::vec3 getRotation();

private:
	glm::vec3 m_worldPosition;
	glm::vec3 m_rotation;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_viewMatrix;
	glm::mat4 m_projViewMatrx;
};