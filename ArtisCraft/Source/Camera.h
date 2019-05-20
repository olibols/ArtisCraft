#include <GLM.h>
#include "Entity.h"

class Camera : public Entity {
public:
	Camera();

	void update();
	void hookEntity(Entity& entity);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
	glm::mat4 getProjectionViewMatrix();

private:
	Entity* m_pEntity;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_projectionViewMatrix;
};